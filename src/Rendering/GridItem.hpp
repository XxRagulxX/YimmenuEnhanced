#pragma once

namespace YimMenu::Rendering
{
	// Base for a single widget in a Grid. Mirrors stand-reference's
	// src/Menu/GridItem.hpp/.cpp: a retained-mode leaf node whose
	// position/size is assigned once by its owning Grid's layout pass, and
	// whose virtual Draw() issues the actual draw calls (via GridRenderer)
	// every frame - no rebuilding of the widget itself per frame.
	class GridItem
	{
	public:
		explicit GridItem(float height) :
		    m_Height(height)
		{
		}

		virtual ~GridItem() = default;

		// Solid-colour/background draws (PrimitiveBatch pass).
		virtual void Draw() = 0;

		// Text draws (SpriteBatch pass, a separate batch type/pipeline
		// state from Draw() above - see GridRenderer::DrawImpl). Default
		// no-op: most items have no text of their own.
		virtual void DrawText()
		{
		}

		void SetPosition(float x, float y, float width)
		{
			m_X = x;
			m_Y = y;
			m_Width = width;
		}

		float GetHeight() const
		{
			return m_Height;
		}

		// Pixel-space hit test against this item's assigned bounds (same
		// coordinate space as GridRenderer::DrawRect/DrawText - top-left
		// origin, Y down). Mirrors stand-reference's own cursor-vs-bounds
		// comparisons (e.g. GridItemList.cpp) rather than any OS hit-testing.
		bool Contains(float cursorX, float cursorY) const
		{
			return cursorX >= m_X && cursorX < m_X + m_Width && cursorY >= m_Y && cursorY < m_Y + m_Height;
		}

		// Called when this item is clicked (cursor was inside Contains()
		// bounds at the moment of a mouse-down). cursorX/Y are given in
		// case a widget needs to know where within itself the click
		// landed (e.g. which segment of a tab strip). Default no-op: most
		// items don't respond to clicks (yet - no real command wiring).
		virtual void OnClick(float cursorX, float cursorY)
		{
		}

	protected:
		float m_X{};
		float m_Y{};
		float m_Width{};
		float m_Height{};
	};
}
