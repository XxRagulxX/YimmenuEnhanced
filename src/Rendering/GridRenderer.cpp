#include "GridRenderer.hpp"

#include "BoolCommand.hpp"
#include "Grid.hpp"
#include "GridItemRect.hpp"
#include "Pointers.hpp"
#include "Renderer.hpp"

#include <RenderTargetState.h>

namespace YimMenu::Rendering
{
	// Visualises the new DirectXTK12 draw pipeline while it's being built
	// out; doesn't touch the existing ImGui menu. Off by default.
	class StandRendererTest : public BoolCommand
	{
		using BoolCommand::BoolCommand;
	};

	static StandRendererTest _StandRendererTest{"standrenderertest",
	    "Stand Renderer Test",
	    "Draws a small stack of test rectangles using the new DirectXTK12/Grid draw pipeline (Stand-style renderer port, WIP)"};

	// Minimal Grid proving out the Grid/GridItem tree: a small stack of
	// solid-colour boxes. Replaced by a real menu grid once text rendering
	// and richer GridItem types (buttons, toggles, ...) land.
	class TestGrid : public Grid
	{
	public:
		TestGrid() :
		    Grid(20.f, 20.f, 220.f)
		{
		}

	protected:
		void Populate() override
		{
			using namespace DirectX;
			m_Items.push_back(std::make_unique<GridItemRect>(28.f, XMFLOAT4(0.85f, 0.1f, 0.1f, 1.f)));
			m_Items.push_back(std::make_unique<GridItemRect>(28.f, XMFLOAT4(0.1f, 0.7f, 0.2f, 1.f)));
			m_Items.push_back(std::make_unique<GridItemRect>(28.f, XMFLOAT4(0.15f, 0.4f, 0.9f, 1.f)));
		}
	};

	static TestGrid g_TestGrid{};

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
		m_States         = std::make_unique<DirectX::CommonStates>(device);

		DirectX::RenderTargetState rtState(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_UNKNOWN);

		DirectX::EffectPipelineStateDescription pd(&DirectX::VertexPositionColor::InputLayout,
		    DirectX::CommonStates::AlphaBlend,
		    DirectX::CommonStates::DepthNone,
		    DirectX::CommonStates::CullNone,
		    rtState,
		    D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE);

		m_Effect = std::make_unique<DirectX::BasicEffect>(device, DirectX::EffectFlags::VertexColor, pd);
		m_Batch  = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(device);
	}

	void GridRenderer::ReleaseDeviceResources()
	{
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

		// ImGui's DX12 backend leaves the viewport/scissor rect set to
		// whatever its last recorded draw command needed, which may be a
		// clipped sub-rect. Reset both to the full backbuffer so our clip
		// space (NDC) coordinates map onto the whole screen as expected.
		const float width  = static_cast<float>(*Pointers.ScreenResX);
		const float height = static_cast<float>(*Pointers.ScreenResY);

		D3D12_VIEWPORT viewport{0.f, 0.f, width, height, 0.f, 1.f};
		D3D12_RECT scissorRect{0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
		commandList->RSSetViewports(1, &viewport);
		commandList->RSSetScissorRects(1, &scissorRect);

		m_Effect->Apply(commandList);
		m_Batch->Begin(commandList);

		g_TestGrid.Draw();

		m_Batch->End();

		m_GraphicsMemory->Commit(Renderer::GetCommandQueue());
	}

	void GridRenderer::DrawRectImpl(float x, float y, float width, float height, const DirectX::XMFLOAT4& colour)
	{
		using namespace DirectX;

		const float screenWidth  = static_cast<float>(*Pointers.ScreenResX);
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

	void GridRenderer::Init()
	{
		Renderer::AddDirect3DDrawCallBack(
		    [](ID3D12GraphicsCommandList* commandList) {
			    GetInstance().DrawImpl(commandList);
		    },
		    0);
	}
}
