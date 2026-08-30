#include "RecoveryGrid.hpp"

#include "GridItemCommandToggle.hpp"
#include "GridItemHeader.hpp"
#include "Joaat.hpp"

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = 26.f;
		constexpr float kItemH = 28.f;
	}

	// Position matches MenuGrid.cpp's kContentX/kContentY exactly (same
	// convention as SelfGrid.cpp/VehicleGrid.cpp/TeleportGrid.cpp/
	// MiscGrid.cpp - no shared header for these yet).
	RecoveryGrid::RecoveryGrid() :
	    Grid(168.f, 94.f, 300.f)
	{
	}

	void RecoveryGrid::Populate()
	{
		// General (MenuRecovery.cpp's generalGroup) - every unconditional
		// BoolCommandItem maps directly onto GridItemCommandToggle.
		// rpmultiplierinput is skipped: it's a ConditionalItem gated on
		// overriderpmultiplier, and this system has no float widget yet.
		m_Items.push_back(std::make_unique<GridItemHeader>(kSectionHeaderH, "General"));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "playallmissionssolo"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "unlockgtaplus"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "overriderpmultiplier"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "freechangeappearance"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "nochangeappearancecooldown"_J));
		m_Items.push_back(std::make_unique<GridItemCommandToggle>(kItemH, "allowgenderchange"_J));

		LOGF(INFO, "[GridRenderer] RecoveryGrid populated with {} items", m_Items.size());
	}
}
