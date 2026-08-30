#include "Grid.hpp"

#include <algorithm>
#include <climits>

namespace YimMenu::Rendering
{
	void Grid::ensurePopulated()
	{
		if (populated)
			return;

		populate(items);
		setPositions(items);
		populated = true;
	}

	// Ported verbatim from Stand's own Grid::setPositions() (Menu/Grid.cpp).
	void Grid::setPositions(const std::vector<std::unique_ptr<GridItem>>& itemsToPosition, size_t recursions) const
	{
		GridItem* last_item = nullptr;
		{
			auto x = origin.x;
			auto y = origin.y;
			for (auto& item : itemsToPosition)
			{
				if (item->keep_pos)
				{
					item->keep_pos = false;
					x = item->x;
					y = item->y;
				}
				else
				{
					if (item->force_alignment_to != nullptr)
					{
						last_item = item->force_alignment_to;
						x = last_item->x;
						y = last_item->y;
					}
					if (last_item == nullptr)
					{
						switch (item->alignment_relative_to_last)
						{
						case ALIGN_TOP_CENTRE:
							y -= item->height;
							break;
						default:
							break;
						}
					}
					else
					{
						switch (item->alignment_relative_to_last)
						{
						case ALIGN_BOTTOM_LEFT:
							y += (last_item->height + spacer_size);
							break;

						case ALIGN_TOP_RIGHT:
							x += (last_item->width + spacer_size);
							break;

						case ALIGN_TOP_LEFT:
							x -= (item->width + spacer_size);
							if (auto* conflict_item = getOccupantNarrow(itemsToPosition, static_cast<int16_t>(x + item->width - 1), static_cast<int16_t>(y + 1), item.get()))
							{
								y += (conflict_item->height + spacer_size);
							}
							break;

						case ALIGN_BOTTOM_RIGHT:
							x -= (item->width - last_item->width);
							break;

						case ALIGN_TOP_CENTRE:
							y -= (item->height + spacer_size);
							break;

						default:
							break;
						}
					}
					item->x = x;
					item->y = y;
					item->onPositioned();
				}
				last_item = item.get();
			}
		}
		last_item = nullptr;
		bool need_redo = false;
		for (auto& item : itemsToPosition)
		{
			if (item->force_alignment_to != nullptr)
			{
				last_item = item->force_alignment_to;
			}
			switch (item->alignment_relative_to_last)
			{
			case ALIGN_BOTTOM_LEFT:
				if (auto* conflict_item = getOccupant(itemsToPosition, static_cast<int16_t>(item->x + item->width - 1), static_cast<int16_t>(item->y + 1), item.get()))
				{
					item->x = static_cast<int16_t>(item->x - (((item->x + item->width) - conflict_item->x) + spacer_size));
					item->keep_pos = true;
					need_redo = true;
				}
				break;

			default:
				break;
			}
			last_item = item.get();
		}
		if (need_redo && ++recursions <= itemsToPosition.size())
		{
			setPositions(itemsToPosition, recursions);
		}
	}

	GridItem* Grid::getOccupant(const std::vector<std::unique_ptr<GridItem>>& items, int16_t x, int16_t y)
	{
		for (const auto& item : items)
		{
			if (item->occupies(x, y))
				return item.get();
		}
		return nullptr;
	}

	GridItem* Grid::getOccupant(const std::vector<std::unique_ptr<GridItem>>& items, int16_t x, int16_t y, GridItem* exclude)
	{
		for (const auto& item : items)
		{
			if (item.get() != exclude && item->occupies(x, y))
				return item.get();
		}
		return nullptr;
	}

	GridItem* Grid::getOccupantNarrow(const std::vector<std::unique_ptr<GridItem>>& items, int16_t x, int16_t y, GridItem* stop_at)
	{
		for (const auto& item : items)
		{
			if (item.get() == stop_at)
				break;

			if (item->occupies(x, y))
				return item.get();
		}
		return nullptr;
	}

	GridItem* Grid::getItemByType(GridItemType target) const
	{
		return getItemByType(items, target);
	}

	GridItem* Grid::getItemByType(const std::vector<std::unique_ptr<GridItem>>& items, GridItemType target)
	{
		for (const auto& item : items)
		{
			if (item->type == target)
				return item.get();
		}
		return nullptr;
	}

	void Grid::draw()
	{
		ensurePopulated();

		for (auto& item : items)
			item->draw();
	}

	void Grid::drawText()
	{
		ensurePopulated();

		for (auto& item : items)
			item->drawText();
	}

	GridItem* Grid::findItemAt(int16_t cursor_x, int16_t cursor_y)
	{
		ensurePopulated();

		return getOccupant(items, cursor_x, cursor_y);
	}

	void Grid::getBounds(int16_t& x1, int16_t& y1, int16_t& x2, int16_t& y2) const
	{
		x1 = SHRT_MAX;
		y1 = SHRT_MAX;
		x2 = 0;
		y2 = 0;
		for (const auto& item : items)
		{
			if (item->x < x1)
				x1 = item->x;
			if (item->y < y1)
				y1 = item->y;

			const auto item_x2 = static_cast<int16_t>(item->x + item->width);
			const auto item_y2 = static_cast<int16_t>(item->y + item->height);
			if (item_x2 > x2)
				x2 = item_x2;
			if (item_y2 > y2)
				y2 = item_y2;
		}
	}

	void Grid::getDimensions(int16_t& x, int16_t& y, int16_t& width, int16_t& height) const
	{
		getBounds(x, y, width, height);
		width -= x;
		height -= y;
	}
}
