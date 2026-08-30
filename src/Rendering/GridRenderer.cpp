#include "GridRenderer.hpp"

#include "BoolCommand.hpp"
#include "GUI.hpp"
#include "MenuGrid.hpp"
#include "MenuNavigation.hpp"
#include "Pointers.hpp"
#include "Renderer.hpp"
#include "font_bevietnamprolight.hpp"

#include <RenderTargetState.h>
#include <ResourceUploadBatch.h>
#include <imgui.h>

namespace YimMenu::Rendering
{
	namespace
	{
		// Cursor position in the same pixel space (client-area, top-left
		// origin) DrawRect/DrawText and Pointers.ScreenResX/Y already use.
		// Nothing in the codebase already exposes this - GUI.cpp's own
		// GetCursorPos/SetCursorPos calls only save/restore the OS cursor
		// across a menu toggle, they don't convert it to this space.
		bool TryGetCursorPos(DirectX::XMFLOAT2& out)
		{
			if (!Pointers.Hwnd || !*Pointers.Hwnd)
				return false;

			POINT cursor;
			if (!GetCursorPos(&cursor))
				return false;

			ScreenToClient(*Pointers.Hwnd, &cursor);
			out = {static_cast<float>(cursor.x), static_cast<float>(cursor.y)};
			return true;
		}
	}

	// Master visibility toggle for the whole DirectXTK12/Grid renderer
	// (MenuGrid below); doesn't touch the existing ImGui menu. Kept the
	// original internal name ("standrenderertest") so existing saved
	// settings.json state isn't lost across the label/description change -
	// it's still the same registered command.
	class StandRendererTest : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		// Log lines here are the easiest way to confirm the toggle itself
		// fired (BoolCommand::SetState runs OnEnable/OnDisable via
		// FiberPool, not the render thread, so this also proves that path
		// works independently of anything DX12-related).
		void OnEnable() override
		{
			LOG(INFO) << "[GridRenderer] Stand Renderer Test enabled";
		}

		void OnDisable() override
		{
			LOG(INFO) << "[GridRenderer] Stand Renderer Test disabled";
		}
	};

	static StandRendererTest _StandRendererTest{"standrenderertest",
	    "Stand Renderer Test",
	    "Shows a Stand-style rebuild of the menu (sidebar + breadcrumb address bar, Backspace to go "
	    "back out of a nested category) using the new DirectXTK12/Grid draw pipeline. Self, Vehicle, "
	    "Teleport, World, Recovery and Debug have real content so far - everything else (including "
	    "any nested category not called out above) shows a placeholder. Use the regular menu for "
	    "anything not yet migrated."};

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
			if (TryGetCursorPos(cursor) && g_MenuGrid.FindItemAt(cursor.x, cursor.y))
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

			g_MenuGrid.Draw();

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

			g_MenuGrid.DrawText();

			m_SpriteBatch->End();
		}

		m_GraphicsMemory->Commit(Renderer::GetCommandQueue());
	}

	void GridRenderer::DrawRectImpl(float x, float y, float width, float height, const DirectX::XMFLOAT4& colour)
	{
		using namespace DirectX;

		const float screenWidth = static_cast<float>(*Pointers.ScreenResX);
		const float screenHeight = static_cast<float>(*Pointers.ScreenResY);

		// Pixel space (top-left origin, Y down) -> clip space / NDC (Y up).
		auto toNdc = [&](float px, float py) {
			return XMFLOAT3((px / screenWidth) * 2.f - 1.f, 1.f - (py / screenHeight) * 2.f, 0.f);
		};

		VertexPositionColor v0(toNdc(x, y), colour);
		VertexPositionColor v1(toNdc(x + width, y), colour);
		VertexPositionColor v2(toNdc(x + width, y + height), colour);
		VertexPositionColor v3(toNdc(x, y + height), colour);

		m_Batch->DrawQuad(v0, v1, v2, v3);
	}

	void GridRenderer::DrawTextImpl(float x, float y, const char* text, const DirectX::XMFLOAT4& colour)
	{
		if (!m_Font || !m_SpriteBatch)
			return;

		m_Font->DrawString(m_SpriteBatch.get(), text, DirectX::XMFLOAT2(x, y), DirectX::XMLoadFloat4(&colour));
	}

	DirectX::XMFLOAT2 GridRenderer::MeasureTextImpl(const char* text) const
	{
		if (!m_Font)
			return {};

		DirectX::XMFLOAT2 size;
		DirectX::XMStoreFloat2(&size, m_Font->MeasureString(text));
		return size;
	}

	void GridRenderer::WndProcImpl(HWND, UINT msg, WPARAM wparam, LPARAM)
	{
		if (!_StandRendererTest.GetState() || !GUI::IsOpen())
			return;

		if (msg == WM_LBUTTONDOWN)
		{
			DirectX::XMFLOAT2 cursor;
			if (!TryGetCursorPos(cursor))
				return;

			if (auto* item = g_MenuGrid.FindItemAt(cursor.x, cursor.y))
				item->OnClick(cursor.x, cursor.y);

			return;
		}

		// Backspace pops MenuNavigation one level - the same "go back"
		// gesture Stand's own address bar responds to. Guarded on
		// WantCaptureKeyboard so this doesn't fire while a text field
		// elsewhere (the existing ImGui menu) has keyboard focus and the
		// user is just backspacing over what they typed there.
		if (msg == WM_KEYDOWN && wparam == VK_BACK && !ImGui::GetIO().WantCaptureKeyboard)
			MenuNavigation::Pop();
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
}
