#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "core/commands/BoolCommand.hpp"

namespace YimMenu::Features
{
	BoolCommand _BusinessOverlay("businessoverlay", "Show Business Overlay", "Displays current Business overlay");

	enum class MCBusinessType
	{
		Forgery = 0,
		Weed,
		Cash,
		Meth,
		Cocaine,
		Bunker,
		None = -1
	};

	static const char* TypeName(MCBusinessType t)
	{
		switch (t)
		{
		case MCBusinessType::Forgery: return "Forgery";
		case MCBusinessType::Weed: return "Weed";
		case MCBusinessType::Cash: return "Cash";
		case MCBusinessType::Meth: return "Meth";
		case MCBusinessType::Cocaine: return "Cocaine";
		case MCBusinessType::Bunker: return "Bunker";
		default: return "None";
		}
	}

	struct PropertyInfo
	{
		Vector3 coords;
		MCBusinessType type;
	};

	struct BusinessRuntime
	{
		int slot{};
		int property{};
		int product{};
		int supplies{};
		MCBusinessType type{};
	};

	static std::vector<BusinessRuntime> g_Businesses;

	static std::unordered_map<int, PropertyInfo> g_PropertyMap = {
	    {1, {{52.903f, 6338.585f, 31.35f}, MCBusinessType::Meth}},
	    {2, {{416.7524f, 6520.753f, 27.7121f}, MCBusinessType::Weed}},
	    {3, {{51.7653f, 6486.163f, 31.428f}, MCBusinessType::Cocaine}},
	    {4, {{-413.6606f, 6171.938f, 31.4782f}, MCBusinessType::Cash}},
	    {5, {{-163.6828f, 6334.845f, 31.5808f}, MCBusinessType::Forgery}},

	    {6, {{1454.671f, -1651.986f, 67.0f}, MCBusinessType::Meth}},
	    {7, {{102.14f, 175.26f, 104.56f}, MCBusinessType::Weed}},
	    {8, {{-1462.622f, -381.826f, 38.802f}, MCBusinessType::Cocaine}},
	    {9, {{-1171.005f, -1380.922f, 4.937f}, MCBusinessType::Cash}},
	    {10, {{299.071f, -759.072f, 29.333f}, MCBusinessType::Forgery}},

	    {11, {{201.8909f, 2461.782f, 55.6885f}, MCBusinessType::Meth}},
	    {12, {{2848.369f, 4450.147f, 48.5139f}, MCBusinessType::Weed}},
	    {13, {{387.5332f, 3585.042f, 33.2922f}, MCBusinessType::Cocaine}},
	    {14, {{636.6344f, 2785.126f, 42.0111f}, MCBusinessType::Cash}},
	    {15, {{1657.066f, 4851.732f, 41.9882f}, MCBusinessType::Forgery}},

	    {16, {{1181.44f, -3113.82f, 6.03f}, MCBusinessType::Meth}},
	    {17, {{136.973f, -2472.795f, 5.98f}, MCBusinessType::Weed}},
	    {18, {{-253.31f, -2591.15f, 5.97f}, MCBusinessType::Cocaine}},
	    {19, {{671.451f, -2667.502f, 6.0812f}, MCBusinessType::Cash}},
	    {20, {{-331.52f, -2778.97f, 5.12f}, MCBusinessType::Forgery}},

	    {21, {{492.8395f, 3014.057f, 39.9793f}, MCBusinessType::Bunker}},
	    {22, {{849.603f, 3021.697f, 40.3076f}, MCBusinessType::Bunker}},
	    {23, {{39.5967f, 2930.506f, 54.8034f}, MCBusinessType::Bunker}},
	    {24, {{1572.078f, 2226.001f, 77.2829f}, MCBusinessType::Bunker}},
	    {25, {{2110.019f, 3326.12f, 44.3526f}, MCBusinessType::Bunker}},
	    {26, {{2489.36f, 3162.12f, 48.0015f}, MCBusinessType::Bunker}},
	    {27, {{1801.273f, 4705.483f, 38.8253f}, MCBusinessType::Bunker}},
	    {28, {{-755.5687f, 5943.835f, 18.9008f}, MCBusinessType::Bunker}},
	    {29, {{-388.8392f, 4340.109f, 55.1741f}, MCBusinessType::Bunker}},
	    {30, {{-3031.356f, 3334.059f, 9.1805f}, MCBusinessType::Bunker}},
	    {31, {{-3157.599f, 1376.695f, 15.866f}, MCBusinessType::Bunker}},
	};

	static int GetBusinessProduct(int slot)
	{
		return Stats::GetInt("MPX_PRODTOTALFORFACTORY" + std::to_string(slot));
	}

	static int GetBusinessSupplies(int slot)
	{
		return Stats::GetInt("MPX_MATTOTALFORFACTORY" + std::to_string(slot));
	}

	static int GetBusinessProperty(int slot)
	{
		return Stats::GetInt("MPX_factoryslot" + std::to_string(slot));
	}

	static void UpdateBusinesses()
	{
		g_Businesses.clear();

		for (int slot = 0; slot <= 5; ++slot)
		{
			int property = GetBusinessProperty(slot);
			if (property <= 0)
				continue;

			auto it = g_PropertyMap.find(property);
			if (it == g_PropertyMap.end())
				continue;

			BusinessRuntime b{};
			b.slot = slot;
			b.property = property;
			b.type = it->second.type;
			b.product = GetBusinessProduct(slot);
			b.supplies = GetBusinessSupplies(slot);

			g_Businesses.push_back(b);
		}
	}

	void DrawBusinessOverlay()
	{
		if (!_BusinessOverlay.GetState())
			return;

		UpdateBusinesses();

		int hangarStock = 0;
		if (auto p = ScriptGlobal(1845299 + 1 + 260 + 304 + 3).As<int*>())
			hangarStock = *p;

		int warehouseStock = 0;
		if (auto p = ScriptGlobal(1845299 + 1 + 260 + 128 + 1).At(0, 3).As<int*>())
			warehouseStock = *p;

		ImGui::Text("Hangar    : %d%% | %d / 50", (hangarStock * 100) / 50, hangarStock);
		ImGui::Text("Warehouse : %d%% | %d / 111", (warehouseStock * 100) / 111, warehouseStock);

		ImGui::Text("Businesses:");

		if (g_Businesses.empty())
		{
			ImGui::TextDisabled("No active businesses");
			return;
		}

		for (const auto& b : g_Businesses)
		{
			ImGui::Text("%s | Slot %d | Stock %d | Supplies %d",
			    TypeName(b.type),
			    b.slot,
			    b.product,
			    b.supplies);
		}
	}
}