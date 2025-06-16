#include "StatEditor.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include "types/stats/CStatsMgr.hpp"
#include <shlobj.h> // For CSIDL constants
#include <Windows.h>

namespace YimMenu::Submenus
{
	struct StatInfo
	{
		std::string m_Name;
		std::uint32_t m_NameHash;
		bool m_Normalized = false;
		sStatData* m_Data = nullptr;

		bool IsValid()
		{
			return m_Data != nullptr;
		}
	};

	struct PackedStatInfo
	{
		int m_Index;
		bool m_IsBoolStat;
		bool m_IsValid;

		bool IsValid()
		{
			return m_IsValid;
		}
	};

	union StatValue {
		float m_AsFloat;
		int m_AsInt;
		bool m_AsBool;
		std::uint64_t m_AsU64;
		char m_AsString[12];
	};

	static StatInfo GetStatInfo(const char* name_str)
	{
		StatInfo name{};
		auto len = strlen(name_str);

		// not sure why people do this
		if (len > 1 && name_str[0] == '$')
		{
			name_str++;
			len--;
			name.m_Normalized = true;
		}

		name.m_Name = name_str;

		if (len > 3 && tolower(name_str[0]) == 'm' && tolower(name_str[1]) == 'p' && tolower(name_str[2]) == 'x')
		{
			if (auto last_char = Pointers.StatsMgr->GetStat("MPPLY_LAST_MP_CHAR"_J))
			{
				name.m_Name[2] = '0' + last_char->GetInt();
				name.m_Normalized = true;
			}
		}

		name.m_NameHash = Joaat(name.m_Name);
		name.m_Data = Pointers.StatsMgr->GetStat(name.m_NameHash);

		if (name.m_Data == nullptr && len > 3 && (tolower(name_str[0]) != 'm' || tolower(name_str[1]) != 'p' || !(tolower(name_str[2]) == '0' || tolower(name_str[2]) == '1')))
		{
			// stat names without a character prefix
			auto last_char = Pointers.StatsMgr->GetStat("MPPLY_LAST_MP_CHAR"_J);
			auto char_index = last_char ? last_char->GetInt() : 0;
			auto char_prefix = char_index == 0 ? "MP0_" : "MP1_";
			auto new_hash = Joaat(char_prefix + name.m_Name);
			auto new_stat = Pointers.StatsMgr->GetStat(new_hash);

			if (new_stat)
			{
				name.m_Name = char_prefix + name.m_Name;
				name.m_NameHash = new_hash;
				name.m_Data = new_stat;
				name.m_Normalized = true;
			}
		}

		return name;
	}

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

	static PackedStatInfo GetPackedStatInfo(int index)
	{
		PackedStatInfo info{};
		int row;
		bool unk;

		info.m_Index = index;
		Pointers.GetPackedStatData(index, &row, &info.m_IsBoolStat, &unk);

		if (row != 0 || index <= 191)
			info.m_IsValid = true;

		return info;
	}

	static void ReadPackedStat(StatValue& value, const PackedStatInfo& info)
	{
		if (info.m_IsBoolStat)
			value.m_AsBool = STATS::GET_PACKED_STAT_BOOL_CODE(info.m_Index, -1);
		else
			value.m_AsInt = STATS::GET_PACKED_STAT_INT_CODE(info.m_Index, -1);
	}

	static void WritePackedStat(const StatValue& value, const PackedStatInfo& info)
	{
		if (info.m_IsBoolStat)
			STATS::SET_PACKED_STAT_BOOL_CODE(info.m_Index, value.m_AsBool, -1);
		else
			STATS::SET_PACKED_STAT_INT_CODE(info.m_Index, value.m_AsInt, -1);
	}

	static void WritePackedStatRange(int start, int end, int value)
	{
		for (int i = start; i <= end; i++)
		{
			auto info = GetPackedStatInfo(i);
			if (!info.m_IsValid)
				break; // the rest are probably not valid, either

			if (info.m_IsBoolStat)
				STATS::SET_PACKED_STAT_BOOL_CODE(info.m_Index, static_cast<bool>(value), -1);
		}
	}

	static bool RenderPackedStatEditor(StatValue& value, const PackedStatInfo& info)
	{
		ImGui::SetNextItemWidth(150.f);
		if (info.m_IsBoolStat)
			return ImGui::Checkbox("Value##packed", &value.m_AsBool);
		else
			return ImGui::InputScalar("Value##packed", ImGuiDataType_U8, &value.m_AsInt);
	}

	static std::string GetStatsFilePath()
	{
		char appdata[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, appdata)))
		{
			std::string path = appdata;
			path += "\\YimMenuV2";
			// Ensure directory exists
			CreateDirectoryA(path.c_str(), NULL);
			path += "\\stats.txt";
			return path;
		}
		return ""; // fallback, should not happen
	}

	static void ProcessStatLines(const std::vector<std::string>& lines)
	{
		if (lines.empty())
		{
			Notifications::Show("Error", "No data to process");
			return;
		}

		int success_count = 0;
		int error_count = 0;

		for (size_t i = 0; i + 1 < lines.size(); i += 2)
		{
			try
			{
				const auto& stat_name = lines[i];
				const auto& stat_value = lines[i + 1];

				auto info = GetStatInfo(stat_name.c_str());
				if (!info.IsValid())
				{
					error_count++;
					continue;
				}

				StatValue value{};
				std::istringstream value_stream(stat_value);

				switch (info.m_Data->GetType())
				{
				case sStatData::Type::_BOOL:
					value_stream >> value.m_AsBool;
					break;
				case sStatData::Type::FLOAT:
					value_stream >> value.m_AsFloat;
					break;
				case sStatData::Type::INT:
				case sStatData::Type::UINT32:
				case sStatData::Type::UINT16:
				case sStatData::Type::UINT8:
					value_stream >> value.m_AsInt;
					break;
				case sStatData::Type::STRING:
					strncpy(value.m_AsString, stat_value.c_str(), sizeof(value.m_AsString));
					break;
				default:
					error_count++;
					continue;
				}

				WriteStat(info.m_NameHash, value, info.m_Data);
				success_count++;
			}
			catch (...)
			{
				error_count++;
			}
		}

		Notifications::Show("Import Complete",
		    std::format("Success: {} | Failed: {}", success_count, error_count));
	}

	static void ImportStatsFromFile()
	{
		std::string stats_path = GetStatsFilePath();
		std::ifstream file(stats_path);

		if (!file.is_open())
		{
			Notifications::Show("Error", "stats.txt not found in DLL folder");
			return;
		}

		std::vector<std::string> lines;
		std::string line;

		while (std::getline(file, line))
		{
			line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
			if (!line.empty())
				lines.push_back(line);
		}

		ProcessStatLines(lines);
	}

	std::shared_ptr<Category> BuildStatEditorMenu()
	{
		auto menu = std::make_shared<Category>("Stat Editor");
		auto normal = std::make_shared<Group>("Regular");
		auto packed = std::make_shared<Group>("Packed");
		auto packed_range = std::make_shared<Group>("Packed Range");
		auto import_group = std::make_shared<Group>("Import Tools");

		import_group->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::Button("Import From TXT"))
			{
				FiberPool::Push([] {
					ImportStatsFromFile();
				});
			}
		}));

		normal->AddItem(std::make_unique<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled("Natives not cached yet");

			static StatInfo current_info;
			static char stat_buf[48]{};
			static StatValue value{};

			ImGui::SetNextItemWidth(300.f);
			if (ImGui::InputText("Name", stat_buf, sizeof(stat_buf)))
			{
				current_info = GetStatInfo(stat_buf);
				if (current_info.IsValid())
					ReadStat(value, current_info.m_Data);
			}

			if (!current_info.IsValid())
				return ImGui::TextDisabled("Stat not found");
			else if (current_info.m_Normalized)
			{
				ImGui::Text("Normalized name to: %s", current_info.m_Name.data());
			}

			bool can_edit = !current_info.m_Data->IsServerAuthoritative() || AnticheatBypass::IsFSLProvidingLocalSaves(); // TODO: a lot of false positives and negatives with this one

			RenderStatEditor(value, current_info.m_Data);

			if (ImGui::Button("Refresh"))
				ReadStat(value, current_info.m_Data);
			ImGui::SameLine();
			ImGui::BeginDisabled(!can_edit);
			if (ImGui::Button("Write"))
				FiberPool::Push([] {
					WriteStat(current_info.m_NameHash, value, current_info.m_Data);
				});
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				FiberPool::Push([] {
					WriteStat(current_info.m_NameHash, value, current_info.m_Data);
				});
			if (!can_edit && ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
				ImGui::SetTooltip("This stat should not be edited by the client. Right-click to force the write anyway");
			ImGui::EndDisabled();
		}));

		packed->AddItem(std::make_unique<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled("Natives not cached yet");

			// TODO: improve packed stat editor
			static PackedStatInfo current_info{0, false, true};
			static StatValue value{};

			ImGui::SetNextItemWidth(200.f);
			if (ImGui::InputInt("Index", &current_info.m_Index))
			{
				current_info = GetPackedStatInfo(current_info.m_Index);
				if (current_info.IsValid())
					ReadPackedStat(value, current_info);
			}

			if (!current_info.IsValid())
				return ImGui::TextDisabled("Index not valid");

			RenderPackedStatEditor(value, current_info);

			if (ImGui::Button("Refresh##packed"))
				ReadPackedStat(value, current_info);
			ImGui::SameLine();
			if (ImGui::Button("Write##packed"))
				FiberPool::Push([] {
					WritePackedStat(value, current_info);
				});
		}));

		packed_range->AddItem(std::make_unique<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled("Natives not cached yet");

			static int start{}, end{}, value{};

			ImGui::SetNextItemWidth(150.f);
			ImGui::InputInt("Start", &start);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150.f);
			ImGui::InputInt("End", &end);
			ImGui::SetNextItemWidth(150.f);
			ImGui::InputScalar("Value##packed_range", ImGuiDataType_U8, &value);
			ImGui::SameLine();
			if (ImGui::Button("Write##packed_range"))
				FiberPool::Push([] {
					WritePackedStatRange(start, end, value);
				});
		}));

		menu->AddItem(std::move(import_group));
		menu->AddItem(std::move(normal));
		menu->AddItem(std::move(packed));
		menu->AddItem(std::move(packed_range));
		return menu;
	}
}