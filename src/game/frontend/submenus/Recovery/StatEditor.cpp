#include "StatEditor.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"
#include "types/stats/CStatsMgr.hpp"

namespace YimMenu::Submenus
{
	union StatValue
	{
		float m_AsFloat;
		int m_AsInt;
		bool m_AsBool;
		std::uint64_t m_AsU64;
		char m_AsString[12];
	};

	static void ReadStat(StatValue& value, sStatData* data)
	{
		memset(&value, 0, sizeof(StatValue));

		switch (data->GetType())
		{
		case sStatData::Type::_BOOL: 
			value.m_AsBool = data->GetBool();
			return;
		case sStatData::Type::FLOAT: 
			value.m_AsFloat = data->GetFloat();
			return;
		case sStatData::Type::INT:
		case sStatData::Type::UINT32: 
		case sStatData::Type::UINT16:
		case sStatData::Type::UINT8: 
			value.m_AsInt = data->GetInt();
			return;
		case sStatData::Type::INT64: 
			value.m_AsU64 = data->GetInt64();
			return;
		case sStatData::Type::UINT64: 
			value.m_AsU64 = data->GetUInt64();
			return;
		case sStatData::Type::STRING: 
			strncpy(value.m_AsString, data->GetString(), sizeof(value.m_AsString));
			return;
		default:
			return; // data type not supported
		}
	}

	static void WriteStat(std::uint32_t hash, StatValue& value, sStatData* data)
	{
		switch (data->GetType())
		{
		case sStatData::Type::_BOOL:
			STATS::STAT_SET_BOOL(hash, value.m_AsBool, true);
			break;
		case sStatData::Type::FLOAT: 
			STATS::STAT_SET_FLOAT(hash, value.m_AsFloat, true);
			return;
		case sStatData::Type::INT:
		case sStatData::Type::UINT32: 
		case sStatData::Type::UINT16:
		case sStatData::Type::UINT8: 
			STATS::STAT_SET_INT(hash, value.m_AsInt, true);
			return;
		case sStatData::Type::INT64: 
			data->SetInt64(value.m_AsU64); // TODO this isn't a good idea! natives can't set this
			return;
		case sStatData::Type::UINT64: 
			STATS::STAT_SET_MASKED_INT(hash, (std::uint32_t)value.m_AsU64, 0, 32, true);
			STATS::STAT_SET_MASKED_INT(hash, (std::uint32_t)(value.m_AsU64 >> 32), 32, 32, true);
			return;
		case sStatData::Type::STRING: 
			STATS::STAT_SET_STRING(hash, value.m_AsString, true);
			return;
		default:
			return; // data type not supported
		}
	}

	static bool RenderStatEditor(StatValue& value, sStatData* data)
	{
		ImGui::SetNextItemWidth(150.f);
		switch (data->GetType())
		{
		case sStatData::Type::_BOOL: 
			return ImGui::Checkbox("Value", &value.m_AsBool);
		case sStatData::Type::FLOAT: 
			return ImGui::InputFloat("Value", &value.m_AsFloat);
		case sStatData::Type::INT:
			return ImGui::InputInt("Value", &value.m_AsInt);
		case sStatData::Type::UINT32: 
			return ImGui::InputScalar("Value", ImGuiDataType_U32, &value.m_AsInt);
		case sStatData::Type::UINT16:
			return ImGui::InputScalar("Value", ImGuiDataType_U16, &value.m_AsInt);
		case sStatData::Type::UINT8: 
			return ImGui::InputScalar("Value", ImGuiDataType_U8, &value.m_AsInt);
		case sStatData::Type::INT64: 
			return ImGui::InputScalar("Value", ImGuiDataType_S64, &value.m_AsInt);
		case sStatData::Type::UINT64: 
			return ImGui::InputScalar("Value", ImGuiDataType_U64, &value.m_AsInt);
		case sStatData::Type::STRING: 
			return ImGui::InputText("Value", value.m_AsString, sizeof(value.m_AsString));
		default:
			ImGui::BeginDisabled();
			ImGui::Text("Data type not supported");
			ImGui::EndDisabled();
			return false; // data type not supported
		}
	}

	std::shared_ptr<Category> BuildStatEditorMenu()
	{
		auto menu = std::make_shared<Category>("Stat Editor");

		menu->AddItem(std::make_unique<ImGuiItem>([] {
			static sStatData* current_stat;
			static char stat_buf[48]{};
			static StatValue value{};

			ImGui::SetNextItemWidth(300.f);
			if (ImGui::InputText("Name", stat_buf, sizeof(stat_buf)))
			{
				current_stat = Pointers.StatsMgr->GetStat(Joaat(stat_buf));
				if (current_stat)
					ReadStat(value, current_stat);
			}

			if (!current_stat)
				return ImGui::Text("Stat not found");

			bool can_edit = !current_stat->IsServerAuthoritative() || AnticheatBypass::IsFSLLoaded(); // TODO: a lot of false positives and negatives with this one

			RenderStatEditor(value, current_stat);

			if (ImGui::Button("Refresh"))
				ReadStat(value, current_stat);
			ImGui::SameLine();
			ImGui::BeginDisabled(!can_edit);
			if (ImGui::Button("Write"))
				FiberPool::Push([] {
					WriteStat(Joaat(stat_buf), value, current_stat);
				});
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				FiberPool::Push([] {
					WriteStat(Joaat(stat_buf), value, current_stat);
				});
			if (!can_edit && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("This stat should not be edited by the client. Right-click to force the write anyway");
			ImGui::EndDisabled();
		}));

		return menu;
	}
}