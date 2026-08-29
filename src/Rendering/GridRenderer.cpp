#include "GridRenderer.hpp"

#include "BoolCommand.hpp"
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
	    "Draws a test rectangle using the new DirectXTK12 draw pipeline (Stand-style renderer port, WIP)"};

	void GridRenderer::EnsureDeviceResources(ID3D12Device* device)
	{
		if (m_Device == device && m_Batch)
			return;

		ReleaseDeviceResources();
		m_Device = device;

		// TODO: once more DirectXTK12-based subsystems exist, GraphicsMemory
		// should be owned centrally (one instance per device, Commit()'d once
		// per frame) rather than per-consumer.
		m_GraphicsMemory = std::make_unique<DirectX::GraphicsMemory>(device, Renderer::GetBufferCount());
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

		using namespace DirectX;

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

		// A small rectangle in the top-left corner, in clip space (NDC), as a
		// smoke test for the DirectXTK12 pipeline. Real screen-space
		// coordinate helpers (Stand's drawRectH/... equivalents) land in a
		// follow-up once this scaffolding is confirmed working.
		constexpr float left   = -0.98f;
		constexpr float right  = -0.70f;
		constexpr float top    = 0.95f;
		constexpr float bottom = 0.85f;
		const XMFLOAT4 red(1.f, 0.f, 0.f, 1.f);

		VertexPositionColor v0(XMFLOAT3(left, top, 0.f), red);
		VertexPositionColor v1(XMFLOAT3(right, top, 0.f), red);
		VertexPositionColor v2(XMFLOAT3(right, bottom, 0.f), red);
		VertexPositionColor v3(XMFLOAT3(left, bottom, 0.f), red);

		m_Batch->DrawQuad(v0, v1, v2, v3);

		m_Batch->End();

		m_GraphicsMemory->Commit(Renderer::GetCommandQueue());
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
