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

		void Draw();
		void DrawText();

	protected:
		// Builds m_Items. Called once, lazily, on the first Draw()/DrawText()
		// (whichever runs first).
		virtual void Populate() = 0;

		std::vector<std::unique_ptr<GridItem>> m_Items;

	private:
		void EnsurePopulated();
		void SetPositions();

		float m_X;
		float m_Y;
		float m_Width;
		bool m_Populated{false};
	};
}
