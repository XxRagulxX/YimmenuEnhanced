#pragma once
#include "Alignment.hpp"
#include "GridItemType.hpp"

#include <climits>
#include <cstdint>

namespace YimMenu::Rendering
{
	// Ported from stand-reference's src/Menu/GridItem.hpp - same fields,
	// same names, same alignment-relative positioning contract (Grid::
	// setPositions() assigns x/y; onPositioned() is the hook a subclass
	// overrides to react). Two differences from Stand's real class:
	//
	// - draw() is split into draw()/drawText(), not one draw(). Stand's
	//   own D3D11 renderer defers every draw call into a sorted list and
	//   flushes it in one pass at frame end, so a single draw() is free
	//   to intermix rect and text calls in any order. This project's
	//   DirectXTK12 renderer instead opens one PrimitiveBatch (rects)
	//   and one SpriteBatch (text) per frame as two separate scopes -
	//   see GridRenderer::DrawImpl - so every item's rect work has to
	//   happen in one pass and its text work in another. Not a stylistic
	//   choice; the two batch types are different pipeline states that
	//   can't be freely interleaved within one Begin/End scope.
	// - onClick() exists here; Stand's own GridItem has no such hook,
	//   since Stand routes interactivity through its Command tree
	//   instead (a GridItemList's rows each resolve back to a Command,
	//   which is what actually reacts to a click) - a whole system this
	//   project hasn't ported. Until it has, GridItem owning its own
	//   click handling is this project's own addition, kept because
	//   every widget built on this base still needs some way to react
	//   to being clicked.
	class GridItem
	{
	public:
		const GridItemType type;
		int16_t x = SHRT_MIN;
		int16_t y = SHRT_MIN;
		int16_t width;
		int16_t height;
		uint8_t priority;
		Alignment alignment_relative_to_last;
		GridItem* force_alignment_to;
		bool keep_pos = false;

		explicit GridItem(GridItemType type,
		    int16_t width,
		    int16_t height,
		    uint8_t priority = 0,
		    Alignment alignment_relative_to_last = ALIGN_BOTTOM_LEFT,
		    GridItem* force_alignment_to = nullptr) :
		    type(type),
		    width(width),
		    height(height),
		    priority(priority),
		    alignment_relative_to_last(alignment_relative_to_last),
		    force_alignment_to(force_alignment_to)
		{
		}

		virtual ~GridItem() = default;

		// Pixel-space hit test against this item's assigned bounds -
		// Stand's own occupies(), used both for click dispatch here and
		// for Grid's own occupancy-conflict resolution during layout.
		[[nodiscard]] bool occupies(int16_t px, int16_t py) const
		{
			return x <= px && px <= (x + width) && y <= py && py <= (y + height);
		}

		// Called by Grid::setPositions() right after it assigns x/y -
		// Stand's own hook for a subclass that needs to react to being
		// (re)positioned. Default no-op, same as Stand's.
		virtual void onPositioned()
		{
		}

		// Solid-colour/background draws (PrimitiveBatch pass). Default
		// no-op: most items look different enough (button fill, toggle
		// indicator, ...) that there's no one shared "background" worth
		// defaulting to, unlike Stand's own draw() (which always paints
		// g_renderer.getBgRectColour() unless overridden).
		virtual void draw()
		{
		}

		// Text draws (SpriteBatch pass) - see the class comment above
		// for why this is separate from draw(). Default no-op: most
		// chrome items have no text of their own.
		virtual void drawText()
		{
		}

		// This project's own addition - see the class comment above.
		// Default no-op: most items don't respond to clicks.
		virtual void onClick(int16_t, int16_t)
		{
		}
	};
}
