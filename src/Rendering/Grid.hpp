#pragma once
#include "GridItem.hpp"
#include "Position2d.hpp"

#include <soup/SharedPtr.hpp>

#include <memory>
#include <vector>

namespace YimMenu::Rendering
{
	// Ported from stand-reference's src/Menu/Grid.hpp - same origin/
	// spacer_size/items fields (items is a soup::SharedPtr-wrapped
	// vector, same as Stand's own - this project already depends on
	// soup elsewhere (src/PatternBatch.hpp, src/Pointers.cpp, ...), so
	// porting Stand code that uses a soup:: type keeps using it rather
	// than substituting something else), same setPositions()/
	// getOccupant()/getItemByType() contract. Differences from Stand's
	// real class:
	//
	// - populate() is called once, lazily, on first use
	//   (ensurePopulated() below) rather than Stand's own repeatable
	//   update()/updateNow() (which reruns populate() on a background
	//   Worker thread whenever a Grid's contents need to change live -
	//   e.g. a saved-locations list changing while the menu is open).
	//   This project has no Worker-driven live-repopulation model yet,
	//   so there's nothing to swap items for after the first populate()
	//   - if a content Grid ever needs to repopulate itself live,
	//   that's the point to add update()/updateNow() for real, using the
	//   FiberPool job queue this project already has instead of Stand's
	//   own Worker.
	// - draw() only does rects; drawText() is this project's own
	//   addition, and findItemAt() too - see GridItem.hpp's class
	//   comment for why (DirectXTK12's two-pass rendering, and this
	//   project not having Stand's Command tree to route clicks through
	//   instead).
	// - No border_width/border_colour/predraw_flags/content_update_queued
	//   - all exist in Stand to support borders and the background
	//   Worker-driven repopulation above, neither of which this project
	//   has yet.
	class Grid
	{
	public:
		Position2d origin;
		int16_t spacer_size;

		explicit Grid(Position2d origin, int16_t spacer_size) :
		    origin(origin),
		    spacer_size(spacer_size)
		{
		}

		explicit Grid(int16_t origin_x, int16_t origin_y, int16_t spacer_size) :
		    Grid(Position2d{origin_x, origin_y}, spacer_size)
		{
		}

		virtual ~Grid() = default;

		virtual void draw();
		virtual void drawText();

		// This project's own addition (see the class comment above) -
		// hit-tests cursor_x/cursor_y against every item via occupies(),
		// same underlying check getOccupant() uses.
		virtual GridItem* findItemAt(int16_t cursor_x, int16_t cursor_y);

		// This project's own addition (see the class comment above) -
		// every item()->isFocusable() in this Grid, in populate() order,
		// for MenuFocus (Up/Down keyboard navigation) to index into. A
		// fresh vector every call rather than a cached one: this Grid's
		// own item list only ever populates once (see ensurePopulated()),
		// so there's no invalidation to track, and any single content
		// Grid's item count is small enough that rebuilding this on every
		// keypress/frame isn't worth the bookkeeping a cache would need.
		[[nodiscard]] std::vector<GridItem*> getFocusableItems();

		// This project's own addition, for the same reason getFocusableItems()
		// is: Stand paginates/scrolls a whole GridItemList's own rows
		// internally (via g_gui.command_rows and its own Command-tree
		// cursor), a system this project doesn't have since - see
		// GridItem.hpp's class comment - every row here is already its
		// own top-level GridItem rather than sub-rows of one list widget.
		// Scrolling the whole Grid's own item list vertically is the
		// equivalent for that shape: draw()/drawText()/findItemAt() all
		// apply the current scroll offset (by temporarily shifting each
		// item's own y, calling through, then restoring it - so no
		// widget needs to know scrolling exists at all) and skip drawing/
		// hit-testing anything that scrolls above origin.y, so a scrolled
		// item can never render on top of whatever sits above this Grid
		// (MenuGrid's own header bar, for a content Grid). Nothing skips
		// the bottom edge the same way - a row scrolled past the visible
		// area's bottom just runs off the real screen's edge, which the
		// GPU clips on its own.
		//
		// Scrolls by delta (H-space, positive = later items), clamped to
		// [0, content height - visibleHeight] (content height from
		// getBounds()). visibleHeight is how tall this Grid's own visible
		// window is (H-space) - not stored on Grid itself, since that
		// depends on where this Grid sits on screen (MenuGrid.cpp/
		// GridRenderer.cpp work it out from Theme::kHudHeight and this
		// Grid's own origin.y).
		void ScrollBy(int16_t delta, int16_t visibleHeight);

		// Scrolls (if needed, via ScrollBy's own clamping) so item's own
		// row is fully within the visible window - MenuGrid::HandleKey()
		// calls this after moving keyboard focus, so focus never lands on
		// a row scrolled out of view without the view following it. A
		// no-op if item is null (nothing focusable in this Grid at all).
		void ScrollToShow(const GridItem* item, int16_t visibleHeight);

	protected:
		// Builds items_draft. Called once, lazily, on first draw()/
		// drawText()/findItemAt() (whichever runs first) - see the class
		// comment above for why this is one-shot rather than Stand's own
		// repeatable update()/updateNow().
		virtual void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) = 0;

	public:
		// Positions every item in-place: walks the list applying each
		// item's alignment_relative_to_last against whatever came before
		// it (or force_alignment_to, if set), then makes a second pass
		// resolving any resulting occupancy conflicts (an ALIGN_BOTTOM_LEFT
		// item landing under something wider than what it was aligned
		// to) by nudging it left and re-running - recursions bounds that
		// to at most items.size() passes. Ported verbatim from Stand's
		// own Grid::setPositions().
		void setPositions(const std::vector<std::unique_ptr<GridItem>>& items, size_t recursions = 0) const;

		[[nodiscard]] static GridItem* getOccupant(const std::vector<std::unique_ptr<GridItem>>& items, int16_t x, int16_t y);
		[[nodiscard]] static GridItem* getOccupant(const std::vector<std::unique_ptr<GridItem>>& items, int16_t x, int16_t y, GridItem* exclude);
		[[nodiscard]] static GridItem* getOccupantNarrow(const std::vector<std::unique_ptr<GridItem>>& items, int16_t x, int16_t y, GridItem* stop_at);

		[[nodiscard]] GridItem* getItemByType(GridItemType target) const;
		[[nodiscard]] static GridItem* getItemByType(const std::vector<std::unique_ptr<GridItem>>& items, GridItemType target);

		void getBounds(int16_t& x1, int16_t& y1, int16_t& x2, int16_t& y2) const;
		void getDimensions(int16_t& x, int16_t& y, int16_t& width, int16_t& height) const;

	protected:
		// Same soup::SharedPtr<std::vector<std::unique_ptr<GridItem>>>
		// Stand's own Grid uses (see the class comment above for why this
		// stays a soup type rather than a plain std::vector) - default-
		// constructed (null) until ensurePopulated()'s first
		// soup::make_shared call.
		soup::SharedPtr<std::vector<std::unique_ptr<GridItem>>> items;

	private:
		void ensurePopulated();

		// Re-clamps m_ScrollOffset to [0, content height - visibleHeight]
		// - shared by ScrollBy() and ScrollToShow(), both of which need
		// it after adjusting m_ScrollOffset their own way.
		void clampScroll(int16_t visibleHeight);

		int16_t m_ScrollOffset = 0;
	};
}
