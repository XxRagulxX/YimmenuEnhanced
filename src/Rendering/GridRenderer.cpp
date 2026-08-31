#include "GridRenderer.hpp"

#include "BoolCommand.hpp"
#include "GUI.hpp"
#include "MenuFocus.hpp"
#include "MenuGrid.hpp"
#include "MenuNavigation.hpp"
#include "MenuPopup.hpp"
#include "Pointers.hpp"
#include "Renderer.hpp"
#include "Theme.hpp"
#include "font_bevietnamprolight.hpp"

#include <RenderTargetState.h>
#include <ResourceUploadBatch.h>
#include <algorithm>
#include <imgui.h>

namespace YimMenu::Rendering
{
	namespace
	{
		// GridItem coordinates (and every Theme.hpp geometry constant)
		// are defined in Stand's own virtual 1920x1080 "H" (HUD) canvas,
		// exactly like stand-reference's own GridItem/Renderer classes
		// (see Rendering/Renderer.hpp's client_size/hudCorrectionC and
		// {size,pos}{H2C,C2H} in Renderer.cpp) - NOT literal client
		// pixels, which is what this project treated them as before and
		// is why the menu was both the wrong size and positioned wrong
		// (MenuGrid's own default_origin only makes sense as an H-space
		// coordinate - see the comment by kHeaderX/kHeaderY in
		// MenuGrid.cpp). H2C below converts an H-space coordinate to a
		// real client pixel for drawing; C2H does the reverse, for
		// turning a real OS cursor position back into the same space
		// GridItem::occupies() and friends compare against.
		//
		// hudCorrection lets a non-16:9 client area (ultrawide, or a
		// window narrower than it is tall) black-bar the extra space
		// instead of stretching the menu's aspect ratio - same as
		// Stand's own hudCorrectionC. kHudWidth/kHudHeight themselves
		// live in Theme.hpp - MenuGrid.cpp needs the same numbers for
		// its own scroll-window math.
		using Theme::kHudHeight;
		using Theme::kHudWidth;

		// One row's worth of scroll per wheel notch (WHEEL_DELTA, 120,
		// per Win32 convention).
		constexpr int16_t kScrollStep = Theme::kContentItemHeight;

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

		DirectX::XMFLOAT2 PosC2H(float x, float y)
		{
			const auto clientSize = GetClientSize();
			const auto correction = GetHudCorrection(clientSize);
			const float cx = x - correction.x;
			const float cy = y - correction.y;
			return {(cx / (clientSize.x - correction.x * 2.f)) * kHudWidth, (cy / (clientSize.y - correction.y * 2.f)) * kHudHeight};
		}

		// Cursor position in H-space (see the block comment above) - what
		// GridItem::occupies() and friends actually compare against.
		// Nothing in the codebase already exposes this - GUI.cpp's own
		// GetCursorPos/SetCursorPos calls only save/restore the OS cursor
		// across a menu toggle, they don't convert it to any of this.
		bool TryGetCursorPos(DirectX::XMFLOAT2& out)
		{
			if (!Pointers.Hwnd || !*Pointers.Hwnd)
				return false;

			POINT cursor;
			if (!GetCursorPos(&cursor))
				return false;

			ScreenToClient(*Pointers.Hwnd, &cursor);
			out = PosC2H(static_cast<float>(cursor.x), static_cast<float>(cursor.y));
			return true;
		}

		// Double-click tracking for GridItem::onClickEx() - same
		// time+target test a real double-click needs (Win32's own
		// GetDoubleClickTime(), same item hit both times). Deliberately
		// not position-threshold-based on top of that: two clicks
		// landing on the same GridItem within the system double-click
		// interval already implies "the same spot" for anything sized
		// like a menu row.
		GridItem* g_LastClickedItem = nullptr;
		ULONGLONG g_LastClickTimeMs = 0;
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
		if (!_StandRendererTest.GetState())
			return;

		if (Renderer::IsResizing())
			return;

		auto device = Renderer::GetDevice();
		if (!device)
			return;

		EnsureDeviceResources(device);

		// Hover suppression: if the cursor is over one of our own items
		// while the menu is open, tell ImGui to claim the mouse for this
		// frame anyway (even though it isn't hovering any ImGui window of
		// its own here) - RawInput.cpp's GetRawInputData hook already
		// suppresses clicks from reaching the game whenever
		// io.WantCaptureMouse is true, so this piggybacks on that existing
		// mechanism instead of building a parallel one.
		if (GUI::IsOpen())
		{
			DirectX::XMFLOAT2 cursor;
			if (TryGetCursorPos(cursor) && g_MenuGrid.findItemAt(static_cast<int16_t>(cursor.x), static_cast<int16_t>(cursor.y)))
				ImGui::SetNextFrameWantCaptureMouse(true);
		}

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

		if (m_Effect && m_Batch)
		{
			m_Effect->Apply(commandList);
			m_Batch->Begin(commandList);

			g_MenuGrid.draw();
			// Drawn last, on top of everything else - see MenuPopup's own
			// class comment for why this is a free-standing overlay
			// rather than a GridItem/Grid of its own.
			MenuPopup::Draw();

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

			g_MenuGrid.drawText();
			MenuPopup::DrawText();

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

		const float screenWidth = static_cast<float>(*Pointers.ScreenResX);
		const float screenHeight = static_cast<float>(*Pointers.ScreenResY);

		// Pixel space (top-left origin, Y down) -> clip space / NDC (Y up).
		auto toNdc = [&](float px, float py) {
			return XMFLOAT3((px / screenWidth) * 2.f - 1.f, 1.f - (py / screenHeight) * 2.f, 0.f);
		};

		VertexPositionColor v0(toNdc(posC.x, posC.y), colour);
		VertexPositionColor v1(toNdc(posC.x + sizeC.x, posC.y), colour);
		VertexPositionColor v2(toNdc(posC.x + sizeC.x, posC.y + sizeC.y), colour);
		VertexPositionColor v3(toNdc(posC.x, posC.y + sizeC.y), colour);

		m_Batch->DrawQuad(v0, v1, v2, v3);
	}

	void GridRenderer::DrawTextImpl(float x, float y, const char* text, const DirectX::XMFLOAT4& colour)
	{
		if (!m_Font || !m_SpriteBatch)
			return;

		// x/y are H-space, same as DrawRectImpl above. The font itself
		// draws at Theme::kTextScale * resolution_text_scale - see
		// Theme::kTextScale's own doc comment for why both factors are
		// needed (the embedded font's native size vs. this project's row
		// heights, and H-space vs. the real client resolution).
		const auto posC = PosH2C(x, y);
		const auto scale = Theme::kTextScale * GetResolutionTextScale(GetClientSize());

		m_Font->DrawString(m_SpriteBatch.get(), text, DirectX::XMFLOAT2(posC.x, posC.y), DirectX::XMLoadFloat4(&colour), 0.f, DirectX::XMFLOAT2{0.f, 0.f}, DirectX::XMFLOAT2{scale, scale});
	}

	DirectX::XMFLOAT2 GridRenderer::MeasureTextImpl(const char* text) const
	{
		if (!m_Font)
			return {};

		// Deliberately NOT multiplied by resolution_text_scale (unlike
		// DrawTextImpl's own scale) - this needs to return a size in the
		// same H-space every GridItem's own x/y/width/height (and this
		// measurement's callers' layout math) is in, and resolution_text_
		// scale is exactly the factor that later converts H-space to the
		// real client resolution. Matches Stand's own getTextWidth()/
		// trimTextH(), which measure using just settings.scale (Theme::
		// kTextScale here), never resolution_text_scale.
		DirectX::XMFLOAT2 size;
		DirectX::XMStoreFloat2(&size, m_Font->MeasureString(text));
		size.x *= Theme::kTextScale;
		size.y *= Theme::kTextScale;
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
		// matched.
		if (MenuPopup::IsOpen())
		{
			if (msg == WM_LBUTTONDOWN)
			{
				DirectX::XMFLOAT2 cursor;
				if (TryGetCursorPos(cursor))
					MenuPopup::HandleClick(static_cast<int16_t>(cursor.x), static_cast<int16_t>(cursor.y));
			}
			else if (msg == WM_KEYDOWN)
			{
				MenuPopup::HandleKey(static_cast<unsigned int>(wparam));
			}

			return;
		}

		// Text-edit interception: while the keyboard-focused item is a
		// GridItemTextInput (or anything built on it) actively editing -
		// see GridItem.hpp's own isEditingText()/onChar()/onEditKey() doc
		// comments - every character/control key goes to it instead of
		// MenuGrid::HandleKey()'s normal list navigation, the same way
		// ImGui's own WantCaptureKeyboard steals input from the game
		// while an ImGui text field has focus. Checked before anything
		// else below (including WM_LBUTTONDOWN's own hit test) since
		// typing shouldn't ever fall through to something else.
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

		if (msg == WM_MOUSEMOVE)
		{
			DirectX::XMFLOAT2 cursor;
			if (TryGetCursorPos(cursor))
			{
				const auto cursorX = static_cast<int16_t>(cursor.x);
				const auto cursorY = static_cast<int16_t>(cursor.y);
				if (auto* item = g_MenuGrid.findItemAt(cursorX, cursorY); item && item->isFocusable())
					MenuFocus::SetFocusedItem(MenuNavigation::Current(), item);
			}

			return;
		}

		if (msg == WM_LBUTTONDOWN)
		{
			DirectX::XMFLOAT2 cursor;
			if (!TryGetCursorPos(cursor))
				return;

			const auto cursorX = static_cast<int16_t>(cursor.x);
			const auto cursorY = static_cast<int16_t>(cursor.y);
			if (auto* item = g_MenuGrid.findItemAt(cursorX, cursorY))
			{
				// Syncs MenuFocus to whatever was just clicked (not just
				// Up/Down-driven navigation) - see SetFocusedItem()'s own
				// doc comment in MenuFocus.hpp for why: it's what makes
				// isKeyboardFocused()'s accent highlight track a mouse
				// click too, and what the text-edit interception above
				// relies on to know which item is "the" one being edited
				// after a click starts editing it.
				if (item->isFocusable())
					MenuFocus::SetFocusedItem(MenuNavigation::Current(), item);

				// Same item, within the system double-click interval - see
				// g_LastClickedItem's own doc comment above for why that's
				// the whole test. Ctrl/Shift read at click time, same as
				// ImGui::IsKeyDown(ImGuiMod_Ctrl/Shift) would in the
				// classic menu's own click handlers.
				const auto nowMs = GetTickCount64();
				const bool doubleClick = item == g_LastClickedItem && (nowMs - g_LastClickTimeMs) <= GetDoubleClickTime();
				g_LastClickedItem = item;
				g_LastClickTimeMs = nowMs;

				const bool ctrlHeld = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
				const bool shiftHeld = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
				item->onClickEx(cursorX, cursorY, ctrlHeld, shiftHeld, doubleClick);
			}

			return;
		}

		if (msg == WM_MOUSEWHEEL)
		{
			// Scrolls whatever content Grid is currently showing - not
			// gated on cursor position (unlike WM_LBUTTONDOWN's hit test
			// above), since this menu has no other scrollable surface to
			// disambiguate against. See Grid::ScrollBy()'s own doc
			// comment for why this exists at all (a content Grid's own
			// item list can be taller than fits on screen, with no
			// pagination/windowing the way Stand's own GridItemList has).
			if (auto* content = MenuNavigation::Current())
			{
				// HIWORD(wparam) is the signed wheel delta (Win32
				// convention) - positive is away from the user (scrolled
				// "up"), which conventionally moves the view toward
				// earlier items, i.e. a negative offset.
				const auto notches = static_cast<short>(HIWORD(wparam)) / WHEEL_DELTA;
				const auto visibleHeight = static_cast<int16_t>(kHudHeight - content->origin.y - Theme::kContentBottomMargin);
				content->ScrollBy(static_cast<int16_t>(-notches * kScrollStep), visibleHeight);
			}
			return;
		}

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
