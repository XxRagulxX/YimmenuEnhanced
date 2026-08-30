#include "SavedVehiclesGrid.hpp"

#include "BoolCommand.hpp"
#include "CommandSavedVehicles.hpp"
#include "Commands.hpp"
#include "FiberPool.hpp"
#include "GridItemButton.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemConditional.hpp"
#include "GridItemSelectList.hpp"
#include "GridItemText.hpp"
#include "GridItemTextInput.hpp"
#include "Joaat.hpp"
#include "MenuPopup.hpp"
#include "Notifications.hpp"
#include "Self.hpp"
#include "Theme.hpp"

#include <format>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// drawSaveVehicleButton()'s own early-return in the original -
		// Save/Populate Name only make sense (and only showed at all)
		// with a valid vehicle to save.
		bool HasValidVehicle()
		{
			auto vehicle = Self::GetVehicle();
			return static_cast<bool>(vehicle);
		}
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	SavedVehiclesGrid::SavedVehiclesGrid() :
	    Grid(1438, 587, 3)
	{
	}

	void SavedVehiclesGrid::RefreshList()
	{
		FiberPool::queueJob([this] {
			SavedVehicles::RefreshList(m_Folder, m_Folders, m_Files);
		});
	}

	void SavedVehiclesGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "spawninsidesavedveh"_J));
		items_draft.push_back(std::make_unique<GridItemButton>(Theme::kContentWidth, kItemH, "Refresh List", [this] {
			RefreshList();
		}));

		// Folder browsing - "Root" (m_Folder == "") prepended to whatever
		// SavedVehicles::RefreshList() last populated m_Folders with;
		// selecting one re-refreshes for that folder, same as the
		// original's own combo's onSelect.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Folder", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemSelectList>(
		    Theme::kContentWidth,
		    "Search folders",
		    [this] {
			    std::vector<std::string> rows{"Root"};
			    rows.insert(rows.end(), m_Folders.begin(), m_Folders.end());
			    return rows;
		    },
		    [this](size_t, const std::string& value, bool, bool, bool) {
			    m_Folder = (value == "Root") ? "" : value;
			    RefreshList();
		    }));

		// Saved vehicles in the current folder - selecting one confirms
		// through MenuPopup (the Phase 1 popup primitive), matching the
		// original's own "Are you sure you want to spawn X" modal
		// exactly.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Saved Vehicles", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemSelectList>(
		    Theme::kContentWidth,
		    "Search",
		    [this] {
			    return m_Files;
		    },
		    [this](size_t, const std::string& value, bool, bool, bool) {
			    MenuPopup::Confirm(std::format("Are you sure you want to spawn {}", value), [this, value] {
				    FiberPool::queueJob([this, value] {
					    auto* spawnInside = Commands::GetCommand<BoolCommand>("spawninsidesavedveh"_J);
					    SavedVehicles::Load(m_Folder, value, spawnInside && spawnInside->GetState());
				    });
			    });
		    }));

		// Save - File Name/New Folder fields always shown (see this
		// class's own header comment for why, unlike the original which
		// hides New Folder outside Root), Populate Name/Save both gated
		// on HasValidVehicle() like the original's shared early-return.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Save", Theme::kText));

		auto fileNameInput = std::make_unique<GridItemTextInput>(Theme::kContentWidth, kItemH, "File Name", "", nullptr);
		m_FileNameInput = fileNameInput.get();
		items_draft.push_back(std::move(fileNameInput));

		auto newFolderInput = std::make_unique<GridItemTextInput>(Theme::kContentWidth, kItemH, "New Folder", "", nullptr);
		m_NewFolderInput = newFolderInput.get();
		items_draft.push_back(std::move(newFolderInput));

		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemButton>(Theme::kContentWidth,
		        kItemH,
		        "Save",
		        [this] {
			        FiberPool::queueJob([this] {
				        if (!m_FileNameInput)
					        return;

				        std::string fileName = m_FileNameInput->GetValue();
				        if (fileName.empty())
				        {
					        Notifications::Show("Saved Vehicles", "Filename empty!", NotificationType::Warning);
					        return;
				        }

				        const bool saveToNewFolder = m_Folder.empty() && m_NewFolderInput && !m_NewFolderInput->GetValue().empty();
				        const std::string targetFolder = saveToNewFolder ? m_NewFolderInput->GetValue() : m_Folder;

				        SavedVehicles::Save(targetFolder, fileName);

				        if (saveToNewFolder)
				        {
					        m_Folder = targetFolder;
					        m_NewFolderInput->SetValue("");
				        }

				        m_FileNameInput->SetValue("");
				        SavedVehicles::RefreshList(m_Folder, m_Folders, m_Files);
			        });
		        }),
		    HasValidVehicle));

		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemButton>(Theme::kContentWidth,
		        kItemH,
		        "Populate Name",
		        [this] {
			        FiberPool::queueJob([this] {
				        auto vehicle = Self::GetVehicle();
				        if (!vehicle || !m_FileNameInput)
					        return;

				        m_FileNameInput->SetValue(vehicle.GetFullName());
			        });
		        }),
		    HasValidVehicle));

		LOGF(INFO, "[GridRenderer] SavedVehiclesGrid populated with {} items", items_draft.size());
	}
}
