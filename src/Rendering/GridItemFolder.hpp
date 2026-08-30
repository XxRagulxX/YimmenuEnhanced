#pragma once
#include "GridItem.hpp"

#include <string>

namespace YimMenu::Rendering
{
	class Grid;

	// A list row ending in a right-aligned ">" - Stand's own way of
	// nesting a category inside another's list instead of a tab/sidebar
	// entry (see e.g. "Spawner >", "Garage >" under its Vehicle submenu).
	// Clicking one drills into m_Target via MenuNavigation::Push();
	// there's no ownership here (m_Target is one of the content Grids
	// like SelfGrid/VehicleGrid already own as file-scope statics, or
	// the shared PlaceholderGrid instance).
	class GridItemFolder : public GridItem
	{
	public:
		GridItemFolder(float height, std::string label, Grid* target) :
		    GridItem(height),
		    m_Label(std::move(label)),
		    m_Target(target)
		{
		}

		void Draw() override;
		void DrawText() override;
		void OnClick(float cursorX, float cursorY) override;

	private:
		std::string m_Label;
		Grid* m_Target;
	};
}
