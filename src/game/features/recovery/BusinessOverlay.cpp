#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/backend/Self.hpp"
#include "types/network/CNetGamePlayer.hpp"

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

	struct WarehouseInfo
	{
		const char* name;
		int capacity;
		Vector3 coords;
	};

	struct WarehouseRuntime
	{
		int slot;
		int property;
		const WarehouseInfo* info;
		int crates;
	};


	int GetLocalPlayerIndex()
	{
		auto player = YimMenu::Self::GetPlayer();

		if (!player)
			return 0;

		return player.GetHandle()->m_PlayerIndex;
	}

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
	static std::vector<WarehouseRuntime> g_Warehouses;

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

	static std::unordered_map<int, WarehouseInfo> g_WarehouseMap = {
	    {1, {"Pacific Bait Storage", 16, {54.191f, -2569.248f, 6.0046f}}},
	    {2, {"White Widow Garage", 16, {-1083.054f, -1261.893f, 5.534f}}},
	    {3, {"Celltowa Unit", 16, {896.3665f, -1035.749f, 35.1096f}}},
	    {4, {"Convenience Store Lockup", 16, {247.473f, -1956.943f, 23.1908f}}},
	    {5, {"Foreclosed Garage", 16, {-424.828f, 185.825f, 80.775f}}},
	    {6, {"Xero Gas Factory", 111, {-1042.482f, -2023.516f, 13.1616f}}},
	    {7, {"Derriere Lingerie Backlot", 42, {-1268.119f, -812.2741f, 17.1075f}}},
	    {8, {"Bilgeco Warehouse", 111, {-873.65f, -2735.948f, 13.9438f}}},
	    {9, {"Pier 400 Utility Building", 16, {274.5224f, -3015.413f, 5.6993f}}},
	    {10, {"GEE Warehouse", 42, {1569.69f, -2129.792f, 78.3351f}}},
	    {11, {"LS Marine Building 3", 42, {-315.551f, -2698.654f, 7.5495f}}},
	    {12, {"Railyard Warehouse", 42, {499.81f, -651.982f, 24.909f}}},
	    {13, {"Fridgit Annexe", 42, {-528.5296f, -1784.573f, 21.5853f}}},
	    {14, {"Disused Factory Outlet", 42, {-295.8596f, -1353.238f, 31.3138f}}},
	    {15, {"Discount Retail Unit", 42, {349.839f, 328.889f, 104.272f}}},
	    {16, {"Logistics Depot", 111, {926.2818f, -1560.311f, 30.7404f}}},
	    {17, {"Darnell Bros Warehouse", 111, {759.566f, -909.466f, 25.244f}}},
	    {18, {"Wholesale Furniture", 111, {1037.813f, -2173.062f, 31.5334f}}},
	    {19, {"Cypress Warehouses", 111, {1019.116f, -2511.69f, 28.302f}}},
	    {20, {"West Vinewood Backlot", 111, {-245.3405f, 203.3286f, 83.818f}}},
	    {21, {"Old Power Station", 42, {539.346f, -1945.682f, 24.984f}}},
	    {22, {"Walker & Sons Warehouse", 111, {96.1538f, -2216.4f, 6.1712f}}},
	};
	static int GetWarehouseCrates(int slot)
	{
		int base = (1845299 + 1 + (GetLocalPlayerIndex() * 880) + 260 + 128) + 1;

		if (auto p = ScriptGlobal(base + 5 + slot).As<int*>())
			return *p;

		return 0;
	}

	static int GetWarehouseOffset()
	{
		int player = GetLocalPlayerIndex();
		return (1845299 + 1 + (player * 880) + 260 + 128) + 1;
	}


	static int GetWarehousePropertyFromSlot(int slot)
	{
		if (auto p = ScriptGlobal(GetWarehouseOffset() + (slot * 3)).As<int*>())
			return *p;
		return 0;
	}


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

	static void UpdateWarehouses()
	{
		g_Warehouses.clear();

		for (int slot = 0; slot < 5; ++slot)
		{
			int property = GetWarehousePropertyFromSlot(slot);
			if (property <= 0)
				continue;

			auto it = g_WarehouseMap.find(property);
			if (it == g_WarehouseMap.end())
				continue;

			WarehouseRuntime w{};
			w.slot = slot;
			w.property = property;
			w.info = &it->second;
			w.crates = GetWarehouseCrates(slot);

			g_Warehouses.push_back(w);
		}
	}

	void DrawBusinessOverlay()
	{
		if (!_BusinessOverlay.GetState())
			return;

		UpdateBusinesses();
		UpdateWarehouses();

		int hangarStock = 0;
		if (auto p = ScriptGlobal(1845299 + 1 + 260 + 304 + 3).As<int*>())
			hangarStock = *p;

		int warehouseStock = 0;
		if (auto p = ScriptGlobal(1845299 + 1 + 260 + 128 + 1).At(0, 3).As<int*>())
			warehouseStock = *p;

		ImGui::Text("Warehouse:");

		ImGui::Text("Hangar    : %d%% | %d / 50", (hangarStock * 100) / 50, hangarStock);
		// ImGui::Text("Warehouse : %d%% | %d / 111", (warehouseStock * 100) / 111, warehouseStock);

		if (g_Warehouses.empty())
		{
			ImGui::TextDisabled("No active Warehouse");
			return;
		}

		for (auto& w : g_Warehouses)
		{
			ImGui::Text("%s | %d / %d crates",
			    w.info->name,
			    w.crates,
			    w.info->capacity);
		}

		ImGui::Text("Businesses:");

		if (g_Businesses.empty())
		{
			ImGui::TextDisabled("No active businesses");
			return;
		}

		for (const auto& b : g_Businesses)
		{
			ImGui::Text("%s | Stock %d | Supplies %d",
			    TypeName(b.type),
			    b.product,
			    b.supplies);
		}
	}
}