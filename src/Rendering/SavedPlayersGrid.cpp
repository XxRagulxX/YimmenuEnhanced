#include "SavedPlayersGrid.hpp"

#include "CommandSavedPlayers.hpp"
#include "FiberPool.hpp"
#include "GridItemBoundToggle.hpp"
#include "GridItemButton.hpp"
#include "GridItemCommandButton.hpp"
#include "GridItemCommandToggle.hpp"
#include "GridItemConditional.hpp"
#include "GridItemLiveText.hpp"
#include "GridItemSelectList.hpp"
#include "GridItemText.hpp"
#include "GridItemTextInput.hpp"
#include "Joaat.hpp"
#include "Network.hpp"
#include "Notifications.hpp"
#include "Theme.hpp"

#include <algorithm>
#include <cstdlib>
#include <format>

namespace YimMenu::Rendering
{
	namespace
	{
		constexpr float kSectionHeaderH = Theme::kContentItemHeight;
		constexpr float kItemH = Theme::kContentItemHeight;

		// RenderPlayerItem()'s own status circle - folded into a
		// bracketed state label instead, see this file's own class
		// comment in the header for why (GridItemSelectList only
		// renders plain text rows). "#<rid>" is always the row's own
		// last token, unambiguous to parse back out in onSelect below
		// since a Rockstar Id is always numeric.
		std::string FormatPlayerRow(std::uint64_t rid, const SavedPlayerData& data)
		{
			auto state = data.m_FetchedData ? std::string(FetchedPlayerData::GameStateToString(data.m_FetchedData->m_GameState)) : std::string("UNKNOWN");
			auto name = data.m_Name.empty() ? std::string("(unnamed)") : data.m_Name;
			return std::format("[{}] {} #{}", state, name, rid);
		}

		std::uint64_t ParseRidFromRow(const std::string& row)
		{
			auto pos = row.rfind('#');
			if (pos == std::string::npos)
				return 0;

			return std::strtoull(row.c_str() + pos + 1, nullptr, 10);
		}
	}

	// Origin (1438, 587) and spacer (3) match every other content Grid's -
	// see the comment in MenuGrid.cpp's anonymous namespace for why (no
	// shared header for these yet). Each item below specifies its own
	// width (Theme::kContentWidth) rather than the Grid itself, matching
	// Stand's real Grid - see Grid.hpp's class comment.
	SavedPlayersGrid::SavedPlayersGrid() :
	    Grid(1438, 587, 3)
	{
	}

	SavedPlayerData* SavedPlayersGrid::SelectedPlayerData() const
	{
		if (!m_SelectedRid)
			return nullptr;

		return SavedPlayers::GetPlayerData(m_SelectedRid);
	}

	void SavedPlayersGrid::populate(std::vector<std::unique_ptr<GridItem>>& items_draft)
	{
		// Players (RenderPlayerList()) - name-sorted (see this file's own
		// header comment for why), selecting one syncs the editor
		// fields below.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Players", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemSelectList>(
		    Theme::kContentWidth,
		    "Search",
		    [] {
			    std::vector<std::string> rows;
			    rows.reserve(SavedPlayers::GetSavedPlayers().size());
			    for (auto& [rid, data] : SavedPlayers::GetSavedPlayers())
				    rows.push_back(FormatPlayerRow(rid, data));
			    std::sort(rows.begin(), rows.end());
			    return rows;
		    },
		    [this](size_t, const std::string& value, bool, bool, bool) {
			    auto rid = ParseRidFromRow(value);
			    if (!rid)
				    return;

			    m_SelectedRid = rid;
			    if (auto* data = SavedPlayers::GetPlayerData(rid))
			    {
				    if (m_NameInput)
					    m_NameInput->SetValue(data->m_Name);
				    if (m_RidInput)
					    m_RidInput->SetValue(std::to_string(rid));
			    }
		    }));

		// Player Editor (RenderPlayerEditor()) - every row gated on a
		// selection existing, matching the original's own "return early
		// with nothing selected" guard.
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Player Editor", Theme::kText));

		auto nameInput = std::make_unique<GridItemTextInput>(Theme::kContentWidth, kItemH, "Name", "", [this](const std::string& value) {
			if (auto* data = SelectedPlayerData())
				data->m_Name = value;
		});
		m_NameInput = nameInput.get();
		items_draft.push_back(std::make_unique<GridItemConditional>(std::move(nameInput), [this] {
			return m_SelectedRid != 0;
		}));

		auto ridInput = std::make_unique<GridItemTextInput>(Theme::kContentWidth, kItemH, "Rockstar Id", "", [this](const std::string& value) {
			const auto newRid = std::strtoull(value.c_str(), nullptr, 10);
			if (!newRid || newRid == m_SelectedRid)
				return;

			// Invalidates every existing SavedPlayerData* (see
			// UpdateRockstarId()'s own TODO comment in
			// CommandSavedPlayers.hpp) - m_NameInput/m_RidInput
			// themselves aren't pointers into it, so nothing else here
			// needs re-syncing.
			SavedPlayers::UpdateRockstarId(m_SelectedRid, newRid);
			m_SelectedRid = newRid;
		});
		m_RidInput = ridInput.get();
		items_draft.push_back(std::make_unique<GridItemConditional>(std::move(ridInput), [this] {
			return m_SelectedRid != 0;
		}));

		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemBoundToggle>(
		        Theme::kContentWidth,
		        kItemH,
		        "Track Player",
		        [this] {
			        auto* data = SelectedPlayerData();
			        return data && data->m_TrackPlayer;
		        },
		        [this](bool value) {
			        if (auto* data = SelectedPlayerData())
				        data->m_TrackPlayer = value;
		        }),
		    [this] {
			    return m_SelectedRid != 0;
		    }));

		// Live session-state readout - the first line covers "nothing
		// selected"/"not fetched yet" for the whole block (matching the
		// original's own single fallback line); the rest just go blank
		// in either case rather than repeating the same message six
		// more times.
		items_draft.push_back(std::make_unique<GridItemLiveText>(
		    Theme::kContentWidth,
		    kItemH,
		    [this] {
			    if (!m_SelectedRid)
				    return std::string();

			    auto* data = SelectedPlayerData();
			    if (!data || !data->m_FetchedData)
				    return std::string("Data not fetched yet");

			    return std::format("Session Type: {}", FetchedPlayerData::GameStateToString(data->m_FetchedData->m_GameState));
		    },
		    Theme::kText));
		items_draft.push_back(std::make_unique<GridItemLiveText>(
		    Theme::kContentWidth,
		    kItemH,
		    [this] {
			    auto* data = SelectedPlayerData();
			    if (!data || !data->m_FetchedData)
				    return std::string();

			    return std::format("Host of Session: {}", data->m_FetchedData->m_HostOfSession ? "Yes" : "No");
		    },
		    Theme::kText));
		items_draft.push_back(std::make_unique<GridItemLiveText>(
		    Theme::kContentWidth,
		    kItemH,
		    [this] {
			    auto* data = SelectedPlayerData();
			    if (!data || !data->m_FetchedData)
				    return std::string();

			    return std::format("Is Spectating: {}", data->m_FetchedData->m_Spectating ? "Yes" : "No");
		    },
		    Theme::kText));
		items_draft.push_back(std::make_unique<GridItemLiveText>(
		    Theme::kContentWidth,
		    kItemH,
		    [this] {
			    auto* data = SelectedPlayerData();
			    if (!data || !data->m_FetchedData)
				    return std::string();

			    return std::format("Is Job Lobby: {}", data->m_FetchedData->m_InTransition ? "Yes" : "No");
		    },
		    Theme::kText));
		items_draft.push_back(std::make_unique<GridItemLiveText>(
		    Theme::kContentWidth,
		    kItemH,
		    [this] {
			    auto* data = SelectedPlayerData();
			    if (!data || !data->m_FetchedData)
				    return std::string();

			    return std::format("Host of Job Lobby: {}", data->m_FetchedData->m_HostOfTransition ? "Yes" : "No");
		    },
		    Theme::kText));
		items_draft.push_back(std::make_unique<GridItemLiveText>(
		    Theme::kContentWidth,
		    kItemH,
		    [this] {
			    auto* data = SelectedPlayerData();
			    if (!data || !data->m_FetchedData || data->m_FetchedData->m_MissionType == FetchedPlayerData::MissionType::NONE)
				    return std::string();

			    return std::format("Mission Type: {}", FetchedPlayerData::MissionTypeToString(data->m_FetchedData->m_MissionType));
		    },
		    Theme::kText));
		items_draft.push_back(std::make_unique<GridItemLiveText>(
		    Theme::kContentWidth,
		    kItemH,
		    [this] {
			    auto* data = SelectedPlayerData();
			    if (!data || !data->m_FetchedData || data->m_FetchedData->m_MissionType == FetchedPlayerData::MissionType::NONE
			        || !data->m_FetchedData->m_MissionName)
				    return std::string();

			    return std::format("Mission Name: {}", *data->m_FetchedData->m_MissionName);
		    },
		    Theme::kText));

		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemButton>(Theme::kContentWidth,
		        kItemH,
		        "Join",
		        [this] {
			        const auto rid = m_SelectedRid;
			        FiberPool::queueJob([rid] {
				        Network::JoinRockstarId(rid);
			        });
		        }),
		    [this] {
			    return m_SelectedRid != 0;
		    }));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemButton>(Theme::kContentWidth,
		        kItemH,
		        "Save",
		        [] {
			        SavedPlayers::Save();
		        }),
		    [this] {
			    return m_SelectedRid != 0;
		    }));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemButton>(Theme::kContentWidth,
		        kItemH,
		        "Remove",
		        [this] {
			        SavedPlayers::RemovePlayerData(m_SelectedRid);
			        m_SelectedRid = 0;
			        if (m_NameInput)
				        m_NameInput->SetValue("");
			        if (m_RidInput)
				        m_RidInput->SetValue("");
		        }),
		    [this] {
			    return m_SelectedRid != 0;
		    }));

		// New (RenderAddNewPlayer())
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "New", Theme::kText));
		auto addUsernameInput = std::make_unique<GridItemTextInput>(Theme::kContentWidth, kItemH, "Username", "", nullptr);
		m_AddUsernameInput = addUsernameInput.get();
		items_draft.push_back(std::move(addUsernameInput));
		items_draft.push_back(std::make_unique<GridItemButton>(Theme::kContentWidth, kItemH, "Add", [this] {
			if (!m_AddUsernameInput)
				return;

			auto username = m_AddUsernameInput->GetValue();
			FiberPool::queueJob([username] {
				if (auto rid = Network::ResolveRockstarId(username))
					SavedPlayers::AddPlayerData(*rid, username);
				else
					Notifications::Show("Saved Players", "Failed to get RID from username", NotificationType::Error);
			});
		}));

		// Tracking (tracking Group)
		items_draft.push_back(std::make_unique<GridItemText>(Theme::kContentWidth, kSectionHeaderH, "Tracking", Theme::kText));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playerdbautoupdate"_J, "Auto Update"));
		items_draft.push_back(std::make_unique<GridItemCommandButton>(Theme::kContentWidth, kItemH, "playerdbupdatenow"_J, "Update Now"));
		items_draft.push_back(std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playerdbnotify"_J, "Tracking Notifications"));

		// Notifications (notifications Group) - gated on playerdbnotify.
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playerdbnotifywhenjoinable"_J),
		    "playerdbnotify"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playerdbnotifywhenunjoinable"_J),
		    "playerdbnotify"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playerdbnotifywhenonline"_J),
		    "playerdbnotify"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playerdbnotifywhenoffline"_J),
		    "playerdbnotify"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playerdbnotifyonseschange"_J),
		    "playerdbnotify"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playerdbnotifyonmischange"_J),
		    "playerdbnotify"_J));
		items_draft.push_back(std::make_unique<GridItemConditional>(
		    std::make_unique<GridItemCommandToggle>(Theme::kContentWidth, kItemH, "playerdbnotifyonjoblobby"_J),
		    "playerdbnotify"_J));

		LOGF(INFO, "[GridRenderer] SavedPlayersGrid populated with {} items", items_draft.size());
	}
}
