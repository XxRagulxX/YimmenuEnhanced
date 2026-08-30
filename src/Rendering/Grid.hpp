#pragma once
#include "GridItem.hpp"

#include <memory>
#include <vector>

namespace YimMenu::Rendering
{
	// Retained-mode widget container, mirroring stand-reference's
	// src/Menu/Grid.hpp/.cpp: Populate() builds the item list once, a
	// layout pass positions them, and Draw() is the only thing that runs
	// every frame after that (no rebuilding of widgets per frame).
	//
	// Layout here is a simple top-down vertical stack for now - Stand's
	// actual alignment/flow-layout system (src/Menu/Alignment.hpp) is
	// follow-up work once real widget types (text, buttons, ...) need it.
	class Grid
	{
	public:
		Grid(float x, float y, float width) :
		    m_X(x),
		    m_Y(y),
		    m_Width(width)
		{
		}

		virtual ~Grid() = default;

		// Virtual so a top-level Grid (MenuGrid) can override these to draw
		// its own chrome items (from m_Items, via Grid::Draw() etc.) and
		// then delegate to whichever content Grid the current
		// sidebar/tab selection points at.
		virtual void Draw();
		virtual void DrawText();

		// Pixel-space hit test (see GridItem::Contains) against every item
		// in this grid. Returns the first item whose bounds contain the
		// cursor, or nullptr. Populates the grid on first call, same as
		// Draw()/DrawText(), so this is safe to call before either has run.
		virtual GridItem* FindItemAt(float cursorX, float cursorY);

	protected:
		// Builds m_Items. Called once, lazily, on the first Draw()/DrawText()
		// (whichever runs first).
		virtual void Populate() = 0;

		// Lays out m_Items after Populate(). Default: a top-down vertical
		// stack, every item given this Grid's own x/width. Override (as a
		// no-op, typically) when items need per-item positioning Populate()
		// already did itself - e.g. MenuGrid's chrome, where the sidebar is
		// a narrower column than the full-width header.
		virtual void SetPositions();

		std::vector<std::unique_ptr<GridItem>> m_Items;

	private:
		void EnsurePopulated();

		float m_X;
		float m_Y;
		float m_Width;
		bool m_Populated{false};
	};
}
