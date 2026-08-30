#pragma once
#include "Grid.hpp"

namespace YimMenu::Rendering
{
	// Content grid for the Players sidebar root: mirrors MenuPlayers.cpp's
	// own DrawPlayerList() (now GridItemPlayerList + a GridItemCommandToggle
	// for "spectate"), then a folder per category. Troll/Toxic/Kick now
	// have real content Grids; Info still points at the shared
	// placeholder - it's a live per-player stats readout (health/coords/
	// rank/RID/platform IDs/IP, several ImGui-only popups and clipboard
	// buttons), a different kind of widget than anything else ported so
	// far and out of scope here.
	class PlayersGrid : public Grid
	{
	public:
		PlayersGrid();

	protected:
		void populate(std::vector<std::unique_ptr<GridItem>>& items_draft) override;
	};
}
