#pragma once
#include "Rendering/Theme.hpp"

#include <CommonStates.h>
#include <Effects.h>
#include <GraphicsMemory.h>
#include <PrimitiveBatch.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <VertexTypes.h>
#include <d3d12.h>
#include <memory>
#include <windows.h>
#include <wrl/client.h>

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
	// This provides pixel-space DrawRect()/DrawText() primitives (Stand's
	// drawRectH/drawTextC equivalents) that Grid/GridItem-based widgets draw
	// themselves with. Text uses the same embedded "Be Vietnam Pro" spritefont
	// blob stand-reference itself ships (see font_bevietnamprolight.hpp).
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

		// Registers our draw/window-procedure callbacks with Renderer. Call
		// once from Main(), after Renderer::Init().
		static void Init();

		// Whether the Stand-style menu is the active UI right now - the
		// registered BoolCommand's own state (still internally named
		// "standrenderertest" for settings.json compatibility; see the
		// note by its registration in GridRenderer.cpp). Menu.cpp checks
		// this to skip drawing the classic ImGui menu entirely while
		// this one is active, rather than drawing both on top of each
		// other - see the note there for what that means for anything
		// not ported to this renderer yet.
		static bool IsActive();

		// Draws a solid-colour rectangle at an H-space position/size
		// (top-left origin, Y down - Stand's own virtual 1920x1080 HUD
		// canvas, same as every GridItem's own x/y/width/height and every
		// Theme.hpp geometry constant), converting to real client pixels
		// and then clip space (NDC) internally - see the block comment by
		// PosH2C/SizeH2C in GridRenderer.cpp. Only valid to call while a
		// batch is open, i.e. from a GridItem::Draw() invoked via Grid::
		// Draw() during our own Direct3DDrawCallBack.
		static void DrawRect(float x, float y, float width, float height, const DirectX::XMFLOAT4& colour)
		{
			GetInstance().DrawRectImpl(x, y, width, height, colour);
		}

		// Draws a UTF-8 text string at an H-space position (top-left
		// origin - see DrawRect's own doc comment above). Only valid to
		// call from a GridItem::DrawText() invoked via Grid::DrawText(),
		// i.e. the separate SpriteBatch pass in DrawImpl. No-ops silently
		// if the embedded font failed to load.
		static void DrawText(float x, float y, const char* text, const DirectX::XMFLOAT4& colour, float scale = Theme::kTextScale)
		{
			GetInstance().DrawTextImpl(x, y, text, colour, scale);
		}

		// Measures a UTF-8 text string in H-space units (x = width,
		// y = height - see DrawRect's own doc comment above), for layout
		// purposes (centering, tab widths, ...) against GridItem's own
		// x/y/width/height. Returns {0, 0} if the embedded font failed to
		// load. Safe to call any time (does not require a batch to be
		// open).
		static DirectX::XMFLOAT2 MeasureText(const char* text, float scale = Theme::kTextScale)
		{
			return GetInstance().MeasureTextImpl(text, scale);
		}

	private:
		static GridRenderer& GetInstance()
		{
			static GridRenderer i{};
			return i;
		}

		void DrawImpl(ID3D12GraphicsCommandList* commandList);
		void WndProcImpl(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		void DrawRectImpl(float x, float y, float width, float height, const DirectX::XMFLOAT4& colour);
		void DrawTextImpl(float x, float y, const char* text, const DirectX::XMFLOAT4& colour, float scale);
		DirectX::XMFLOAT2 MeasureTextImpl(const char* text, float scale) const;

		void EnsureDeviceResources(ID3D12Device* device);
		void ReleaseDeviceResources();

	private:
		ID3D12Device* m_Device{};

		std::unique_ptr<DirectX::GraphicsMemory> m_GraphicsMemory;
		std::unique_ptr<DirectX::CommonStates> m_States;
		std::unique_ptr<DirectX::BasicEffect> m_Effect;
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_Batch;

		// Text (only created if the embedded font loads successfully -
		// DrawTextImpl no-ops otherwise, DrawRect/the rest of the pipeline
		// is unaffected).
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_FontDescriptorHeap;
		std::unique_ptr<DirectX::SpriteFont> m_Font;
		std::unique_ptr<DirectX::SpriteBatch> m_SpriteBatch;
	};
}
