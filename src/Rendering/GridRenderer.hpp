#pragma once
#include <CommonStates.h>
#include <Effects.h>
#include <GraphicsMemory.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <d3d12.h>
#include <memory>

namespace YimMenu::Rendering
{
	// First slice of the Stand-style custom renderer port: a DirectXTK12-backed
	// draw-primitives layer that records into the same per-frame D3D12 command
	// list the existing ImGui menu already uses (wired up via
	// Renderer::AddDirect3DDrawCallBack), rather than replacing it.
	//
	// Modeled after stand-reference's src/Rendering/Renderer.hpp/.cpp, which
	// is built on DirectXTK (D3D11) - this is the DirectXTK12/D3D12 equivalent,
	// since this project's swapchain is D3D12.
	//
	// This is intentionally minimal for now (one hardcoded test primitive,
	// gated behind the "standrenderertest" debug toggle) - the real
	// screen-space draw helpers (Stand's drawRectH/drawTextC/... equivalents)
	// and the Grid/GridItem retained-mode widget tree land in follow-ups once
	// this scaffolding is confirmed working end-to-end.
	class GridRenderer final
	{
	private:
		GridRenderer() = default;

	public:
		~GridRenderer() = default;

		GridRenderer(const GridRenderer&) = delete;
		GridRenderer(GridRenderer&&) noexcept = delete;
		GridRenderer& operator=(const GridRenderer&) = delete;
		GridRenderer& operator=(GridRenderer&&) noexcept = delete;

		// Registers our draw callback with Renderer. Call once from Main(),
		// after Renderer::Init().
		static void Init();

	private:
		static GridRenderer& GetInstance()
		{
			static GridRenderer i{};
			return i;
		}

		void DrawImpl(ID3D12GraphicsCommandList* commandList);

		void EnsureDeviceResources(ID3D12Device* device);
		void ReleaseDeviceResources();

	private:
		ID3D12Device* m_Device{};

		std::unique_ptr<DirectX::GraphicsMemory> m_GraphicsMemory;
		std::unique_ptr<DirectX::CommonStates> m_States;
		std::unique_ptr<DirectX::BasicEffect> m_Effect;
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_Batch;
	};
}
