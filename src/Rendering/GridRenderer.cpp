#include "Rendering/GridRenderer.hpp"

#include "Commands/BoolCommand.hpp"
#include "Menu/GUI.hpp"
#include "Rendering/ESP.hpp"
#include "Rendering/MenuFocus.hpp"
#include "Rendering/MenuGrid.hpp"
#include "Rendering/MenuNavigation.hpp"
#include "Rendering/MenuPopup.hpp"
#include "Core/Pointers.hpp"
#include "Rendering/Notifications.hpp"
#include "Rendering/Overlay.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/Theme.hpp"
#include "Rendering/font_bevietnamprolight.hpp"

#include <RenderTargetState.h>
#include <ResourceUploadBatch.h>
#include <algorithm>
#include <cmath>
#include <imgui.h>

namespace YimMenu::Rendering
{
	namespace
	{
		// GridItem coordinates (and every Theme.hpp geometry constant)
		// are defined in Stand's own virtual 1920x1080 "H" (HUD) canvas,
		// exactly like stand-reference's own GridItem/Renderer classes
		// (see Rendering/Renderer.hpp's client_size/hudCorrectionC and
		// {size,pos}H2C in Renderer.cpp) - NOT literal client pixels,
		// which is what this project treated them as before and is why
		// the menu was both the wrong size and positioned wrong
		// (MenuGrid's own default_origin only makes sense as an H-space
		// coordinate - see the comment by kHeaderX/kHeaderY in
		// MenuGrid.cpp). H2C below converts an H-space coordinate to a
		// real client pixel for drawing. There's deliberately no C2H
		// (OS cursor position -> H-space) any more - this menu is
		// keyboard-only, no mouse, so nothing ever needs to convert a
		// cursor position at all.
		//
		// hudCorrection lets a non-16:9 client area (ultrawide, or a
		// window narrower than it is tall) black-bar the extra space
		// instead of stretching the menu's aspect ratio - same as
		// Stand's own hudCorrectionC. kHudWidth/kHudHeight themselves
		// live in Theme.hpp - MenuGrid.cpp needs the same numbers for
		// its own scroll-window math.
		using Theme::kHudHeight;
		using Theme::kHudWidth;

		DirectX::XMFLOAT2 GetClientSize()
		{
			return {static_cast<float>(*Pointers.ScreenResX), static_cast<float>(*Pointers.ScreenResY)};
		}

		DirectX::XMFLOAT2 GetHudCorrection(const DirectX::XMFLOAT2& clientSize)
		{
			const float expectedWidth = clientSize.y * (16.f / 9.f);
			if (clientSize.x > expectedWidth)
				return {(clientSize.x - expectedWidth) * 0.5f, 0.f};

			const float expectedHeight = clientSize.x * (9.f / 16.f);
			return {0.f, (clientSize.y - expectedHeight) * 0.5f};
		}

		// Stand's own resolution_text_scale - see Theme::kTextScale's own
		// doc comment for why text needs this on top of that fixed scale.
		float GetResolutionTextScale(const DirectX::XMFLOAT2& clientSize)
		{
			return std::min(clientSize.x / kHudWidth, clientSize.y / kHudHeight);
		}

		DirectX::XMFLOAT2 SizeH2C(float x, float y)
		{
			const auto clientSize = GetClientSize();
			const auto correction = GetHudCorrection(clientSize);
			return {(x / kHudWidth) * (clientSize.x - correction.x * 2.f), (y / kHudHeight) * (clientSize.y - correction.y * 2.f)};
		}

		DirectX::XMFLOAT2 PosH2C(float x, float y)
		{
			const auto clientSize = GetClientSize();
			const auto correction = GetHudCorrection(clientSize);
			const auto size = SizeH2C(x, y);
			return {size.x + correction.x, size.y + correction.y};
		}

		// Real client pixel space (top-left origin, Y down) -> clip
		// space / NDC (Y up) - shared by DrawRectImpl and
		// DrawLineScreenImpl (the only two consumers of raw NDC quads;
		// DrawTextImpl/DrawTextScreenImpl hand SpriteFont pixel
		// coordinates directly and never need this).
		DirectX::XMFLOAT3 PixelToNdc(float px, float py)
		{
			const auto clientSize = GetClientSize();
			return {(px / clientSize.x) * 2.f - 1.f, 1.f - (py / clientSize.y) * 2.f, 0.f};
		}
	}

	// Master visibility toggle for the whole DirectXTK12/Grid renderer
	// (MenuGrid below). OFF by default while this is still being built
	// out to match stand-reference's real Menu/Grid.*/GridItem.* classes
	// 1:1 - the classic ImGui menu is the primary UI for now, and this
	// is an opt-in way to check the Grid port's progress (Debug > Misc's
	// "Stand-Style Menu" toggle, in both the classic menu and this
	// renderer's own Debug > Misc page) without losing the working menu
	// underneath it. Menu.cpp's own renderer callback checks
	// GridRenderer::IsActive() and skips UIManager::Draw() (the classic
	// ImGui menu) entirely while this is true, rather than drawing both
	// on top of each other. Kept the original internal name
	// ("standrenderertest") so existing saved settings.json state isn't
	// lost across the label/description/default change - it's still the
	// same registered command.
	class StandRendererTest : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		// Log lines here are the easiest way to confirm the toggle itself
		// fired (BoolCommand::SetState runs OnEnable/OnDisable via
		// FiberPool, not the render thread, so this also proves that path
		// works independently of anything DX12-related).
		void OnEnable() override
		{
			LOG(INFO) << "[GridRenderer] Stand-style menu enabled - classic ImGui menu now hidden while this is open";
		}

		void OnDisable() override
		{
			LOG(INFO) << "[GridRenderer] Stand-style menu disabled - classic ImGui menu is back";
		}
	};

	static StandRendererTest _StandRendererTest{"standrenderertest",
	    "Stand-Style Menu",
	    "The DirectXTK12/Grid draw pipeline being ported from stand-reference's own Menu/Grid.* and "
	    "Menu/GridItem.* (alignment-relative layout and all), still under active development - OFF by "
	    "default, with the classic ImGui menu as the primary UI. Turn this on to check the Grid port's "
	    "progress (sidebar + breadcrumb address bar, Backspace to go back out of a nested category) "
	    "alongside the classic menu; while it's on, the classic ImGui menu doesn't draw at all, so turn "
	    "it back off to get it back for anything not ported here yet.",
	    false};

	static MenuGrid g_MenuGrid{};

	void GridRenderer::EnsureDeviceResources(ID3D12Device* device)
	{
		if (m_Device == device && m_Batch)
			return;

		ReleaseDeviceResources();
		m_Device = device;

		// TODO: once more DirectXTK12-based subsystems exist, GraphicsMemory
		// should be owned centrally (one instance per device, Commit()'d once
		// per frame) rather than per-consumer.
		m_GraphicsMemory = std::make_unique<DirectX::GraphicsMemory>(device);
		m_States = std::make_unique<DirectX::CommonStates>(device);

		DirectX::RenderTargetState rtState(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_UNKNOWN);

		DirectX::EffectPipelineStateDescription pd(&DirectX::VertexPositionColor::InputLayout,
		    DirectX::CommonStates::AlphaBlend,
		    DirectX::CommonStates::DepthNone,
		    DirectX::CommonStates::CullNone,
		    rtState,
		    D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);

		m_Effect = std::make_unique<DirectX::BasicEffect>(device, DirectX::EffectFlags::VertexColor, pd);
		m_Batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(device);

		LOG(INFO) << "[GridRenderer] DirectXTK12 rect pipeline ready";

		// Text: embedded "Be Vietnam Pro" spritefont (see
		// font_bevietnamprolight.hpp). Failure here (e.g. a malformed blob)
		// is non-fatal - DrawTextImpl no-ops if m_Font/m_SpriteBatch are
		// null, and rect drawing above is unaffected.
		D3D12_DESCRIPTOR_HEAP_DESC fontHeapDesc{
		    D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		    1,
		    D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE};
		if (const auto result = device->CreateDescriptorHeap(&fontHeapDesc,
		        __uuidof(ID3D12DescriptorHeap),
		        (void**)m_FontDescriptorHeap.ReleaseAndGetAddressOf());
		    result < 0)
		{
			LOGF(WARNING, "[GridRenderer] Failed to create font descriptor heap with result: [{}]", result);
		}
		else
		{
			try
			{
				DirectX::ResourceUploadBatch upload(device);
				upload.Begin();

				m_Font = std::make_unique<DirectX::SpriteFont>(device,
				    upload,
				    reinterpret_cast<const uint8_t*>(font_bevietnamprolight::chunk_1),
				    sizeof(font_bevietnamprolight::chunk_1),
				    m_FontDescriptorHeap->GetCPUDescriptorHandleForHeapStart(),
				    m_FontDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
				m_Font->SetDefaultCharacter(L'?');

				DirectX::SpriteBatchPipelineStateDescription spritePd(rtState);
				m_SpriteBatch = std::make_unique<DirectX::SpriteBatch>(device, upload, spritePd);

				upload.End(Renderer::GetCommandQueue()).wait();

				LOG(INFO) << "[GridRenderer] Embedded font loaded, text pipeline ready";
			}
			catch (const std::exception& e)
			{
				LOGF(WARNING, "[GridRenderer] Failed to load embedded font: {}", e.what());
				m_Font.reset();
				m_SpriteBatch.reset();
			}
		}
	}

	void GridRenderer::ReleaseDeviceResources()
	{
		m_SpriteBatch.reset();
		m_Font.reset();
		m_FontDescriptorHeap.Reset();
		m_Batch.reset();
		m_Effect.reset();
		m_States.reset();
		m_GraphicsMemory.reset();
		m_Device = nullptr;
	}

	void GridRenderer::DrawImpl(ID3D12GraphicsCommandList* commandList)
	{
		// No menu/Insert-toggle gate up here any more, unlike before
		// Notifications moved onto this pipeline - toasts have to draw
		// every frame regardless of whether the Stand-style menu is even
		// open (see Notifications.hpp's own class comment), so resource
		// setup and the two batches below always run now; menuActive
		// below is what still gates the menu/popup content specifically.
		if (Renderer::IsResizing())
			return;

		auto device = Renderer::GetDevice();
		if (!device)
			return;

		EnsureDeviceResources(device);

		// No mouse-hover suppression here any more - this menu is
		// keyboard-only, nothing in it ever reacts to the cursor (see
		// WndProcImpl below), so there's nothing that would need to
		// steal ImGui's mouse capture on its behalf.

		// ImGui's DX12 backend leaves the viewport/scissor rect set to
		// whatever its last recorded draw command needed, which may be a
		// clipped sub-rect. Reset both to the full backbuffer so our clip
		// space (NDC) coordinates map onto the whole screen as expected.
		const float width = static_cast<float>(*Pointers.ScreenResX);
		const float height = static_cast<float>(*Pointers.ScreenResY);

		D3D12_VIEWPORT viewport{0.f, 0.f, width, height, 0.f, 1.f};
		D3D12_RECT scissorRect{0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
		commandList->RSSetViewports(1, &viewport);
		commandList->RSSetScissorRects(1, &scissorRect);

		// Same gate WndProcImpl already applies to input - the menu/popup
		// content stays tied to GUI::IsOpen()/the Insert toggle, or the
		// menu stays on screen (and stays the active UI, since Menu.cpp
		// skips the classic ImGui menu entirely while this is active)
		// regardless of it. Notifications below are deliberately outside
		// this gate.
		const bool menuActive = _StandRendererTest.GetState() && GUI::IsOpen();

		if (m_Effect && m_Batch)
		{
			m_Effect->Apply(commandList);
			m_Batch->Begin(commandList);

			if (menuActive)
			{
				g_MenuGrid.draw();
				// Drawn last, on top of everything else - see MenuPopup's
				// own class comment for why this is a free-standing
				// overlay rather than a GridItem/Grid of its own.
				MenuPopup::Draw();
			}

			// Always drawn, regardless of menuActive above - see
			// Notifications.hpp's own class comment (Overlay.cpp's own
			// watermark-style FPS/business overlay, and ESP, are the
			// same shape: always visible, independent of any menu).
			Notifications::Draw();
			Overlay::Draw();
			ESP::Draw();

			m_Batch->End();
		}

		// Separate pass/batch type from the rects above: SpriteBatch manages
		// its own root signature + PSO (set in Begin()) and needs the font's
		// SRV descriptor heap bound, which replaces whatever heap ImGui left
		// bound - safe here since ImGui has already finished recording its
		// own draws for this frame by the time our callback runs.
		if (m_Font && m_SpriteBatch && m_FontDescriptorHeap)
		{
			commandList->SetDescriptorHeaps(1, m_FontDescriptorHeap.GetAddressOf());

			m_SpriteBatch->SetViewport(viewport);
			m_SpriteBatch->Begin(commandList);

			if (menuActive)
			{
				g_MenuGrid.drawText();
				MenuPopup::DrawText();
			}

			Notifications::DrawText();
			Overlay::DrawText();
			ESP::DrawText();

			m_SpriteBatch->End();
		}

		m_GraphicsMemory->Commit(Renderer::GetCommandQueue());
	}

	void GridRenderer::DrawRectImpl(float x, float y, float width, float height, const DirectX::XMFLOAT4& colour)
	{
		using namespace DirectX;

		// x/y/width/height are H-space (see the block comment by
		// PosH2C/SizeH2C above) - convert to real client pixels before
		// building NDC coordinates below.
		const auto posC = PosH2C(x, y);
		const auto sizeC = SizeH2C(width, height);

		VertexPositionColor v0(PixelToNdc(posC.x, posC.y), colour);
		VertexPositionColor v1(PixelToNdc(posC.x + sizeC.x, posC.y), colour);
		VertexPositionColor v2(PixelToNdc(posC.x + sizeC.x, posC.y + sizeC.y), colour);
		VertexPositionColor v3(PixelToNdc(posC.x, posC.y + sizeC.y), colour);

		m_Batch->DrawQuad(v0, v1, v2, v3);
	}

	void GridRenderer::DrawLineScreenImpl(float x1, float y1, float x2, float y2, const DirectX::XMFLOAT4& colour, float thickness)
	{
		using namespace DirectX;

		if (!m_Batch)
			return;

		// A thin quad along the line rather than a real GPU line
		// primitive - see GridRenderer.hpp's own DrawLineScreen doc
		// comment for why (reuses this same PrimitiveBatch/PSO, and
		// gives real thickness control ImGui's own AddLine had that a
		// 1px D3D12 line primitive wouldn't).
		const float dx = x2 - x1;
		const float dy = y2 - y1;
		const float length = std::sqrt(dx * dx + dy * dy);
		if (length < 0.0001f)
			return;

		const float nx = -dy / length * (thickness * 0.5f);
		const float ny = dx / length * (thickness * 0.5f);

		VertexPositionColor v0(PixelToNdc(x1 + nx, y1 + ny), colour);
		VertexPositionColor v1(PixelToNdc(x2 + nx, y2 + ny), colour);
		VertexPositionColor v2(PixelToNdc(x2 - nx, y2 - ny), colour);
		VertexPositionColor v3(PixelToNdc(x1 - nx, y1 - ny), colour);

		m_Batch->DrawQuad(v0, v1, v2, v3);
	}

	void GridRenderer::DrawTextImpl(float x, float y, const char* text, const DirectX::XMFLOAT4& colour, float scale)
	{
		if (!m_Font || !m_SpriteBatch)
			return;

		const auto posC = PosH2C(x + Theme::kTextOffsetX, y + Theme::kTextOffsetY);
		const auto finalScale = scale * GetResolutionTextScale(GetClientSize());

		m_Font->DrawString(m_SpriteBatch.get(), text, DirectX::XMFLOAT2(posC.x, posC.y), DirectX::XMLoadFloat4(&colour), 0.f, DirectX::XMFLOAT2{0.f, 0.f}, DirectX::XMFLOAT2{finalScale, finalScale});
	}

	void GridRenderer::DrawTextScreenImpl(float x, float y, const char* text, const DirectX::XMFLOAT4& colour, float scale)
	{
		if (!m_Font || !m_SpriteBatch)
			return;

		// Real client pixels, no PosH2C/resolution-scale correction -
		// see GridRenderer.hpp's own DrawTextScreen doc comment for why.
		m_Font->DrawString(m_SpriteBatch.get(), text, DirectX::XMFLOAT2(x, y), DirectX::XMLoadFloat4(&colour), 0.f, DirectX::XMFLOAT2{0.f, 0.f}, DirectX::XMFLOAT2{scale, scale});
	}

	DirectX::XMFLOAT2 GridRenderer::MeasureTextImpl(const char* text, float scale) const
	{
		if (!m_Font)
			return {};

		DirectX::XMFLOAT2 size;
		DirectX::XMStoreFloat2(&size, m_Font->MeasureString(text));
		size.x *= scale;
		size.y *= scale;
		return size;
	}

	void GridRenderer::WndProcImpl(HWND, UINT msg, WPARAM wparam, LPARAM)
	{
		if (!_StandRendererTest.GetState() || !GUI::IsOpen())
			return;

		// MenuPopup takes over every input while open, ahead of even the
		// text-edit interception right below - a popup open on top of a
		// text field mid-edit still wins. See MenuPopup's own class
		// comment for why it always swallows regardless of what it
		// matched. Keyboard-only, same as everything else here - no
		// mouse click path.
		if (MenuPopup::IsOpen())
		{
			if (msg == WM_KEYDOWN)
				MenuPopup::HandleKey(static_cast<unsigned int>(wparam));

			return;
		}

		// Text-edit interception: while the keyboard-focused item is a
		// GridItemTextInput (or anything built on it) actively editing -
		// see GridItem.hpp's own isEditingText()/onChar()/onEditKey() doc
		// comments - every character/control key goes to it instead of
		// MenuGrid::HandleKey()'s normal list navigation, the same way
		// ImGui's own WantCaptureKeyboard steals input from the game
		// while an ImGui text field has focus. Checked before anything
		// else below since typing shouldn't ever fall through to
		// something else.
		if (auto* focused = MenuFocus::GetFocusedItem(MenuNavigation::Current()); focused && focused->isEditingText())
		{
			if (msg == WM_CHAR)
			{
				focused->onChar(static_cast<wchar_t>(wparam));
				return;
			}

			if (msg == WM_KEYDOWN)
			{
				focused->onEditKey(static_cast<unsigned int>(wparam));
				return;
			}
		}

		// No WM_MOUSEMOVE/WM_LBUTTONDOWN/WM_MOUSEWHEEL handling - this
		// menu is keyboard-only by design (real Stand feel: no mouse
		// cursor, no click-to-select, no wheel-scroll). Keyboard focus
		// moves via MenuGrid::HandleKey()'s Up/Down (content) and Left
		// Ctrl/Shift (sidebar) below, which already calls
		// Grid::ScrollToShow() to keep the focused row in view, so
		// there's no scrollable surface a wheel would even be needed
		// for.

		// Every other key this system responds to (Up/Down/Left/Right/
		// Enter/Backspace - see MenuGrid::HandleKey()) - guarded on
		// WantCaptureKeyboard so this doesn't fire while a text field
		// elsewhere (the existing ImGui menu) has keyboard focus and the
		// user is just typing there. WM_KEYDOWN repeats while a key is
		// held (standard Win32 auto-repeat), which is exactly the "hold
		// Down to keep moving" feel a menu like this should have -
		// nothing extra needed here for that.
		if (msg == WM_KEYDOWN && !ImGui::GetIO().WantCaptureKeyboard)
			g_MenuGrid.HandleKey(static_cast<unsigned int>(wparam));
	}

	void GridRenderer::Init()
	{
		Renderer::AddDirect3DDrawCallBack(
		    [](ID3D12GraphicsCommandList* commandList) {
			    GetInstance().DrawImpl(commandList);
		    },
		    0);

		Renderer::AddWindowProcedureCallback([](HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			GetInstance().WndProcImpl(hwnd, msg, wparam, lparam);
		});
	}

	bool GridRenderer::IsActive()
	{
		return _StandRendererTest.GetState();
	}
}
