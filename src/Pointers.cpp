#include "Pointers.hpp"

#include "ModuleMgr.hpp"
#include "Joaat.hpp"
#include "atArray.hpp"
#include "PatternBatch.hpp"
#include <LogHelper.hpp>

namespace YimMenu
{
	// on some cracked game builds
	static bool IsSocialClubNeverGoingToLoad()
	{
		return Pointers.ScriptThreads && Pointers.ScriptThreads->size() != 0;
	}

	bool Pointers::Init()
	{

		const auto gta5 = g_ModuleMgr.Get("GTA5_Enhanced.exe"_J);

		if (!gta5)
		{
			LOG(FATAL) << "Could not find GTA5_Enhanced.exe, is this GTA 5 Enhanced?";
			return false;
		}

		std::unordered_map<std::string, std::uintptr_t> patternBatchCache;
		PatternBatch batch(&patternBatchCache);


		soup::Range versionRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern versionPattern("4C 8D 0D ? ? ? ? 48 8D 5C 24 ? 48 89 D9 48 89 FA");
		batch.Add("Version", std::move(versionRange), std::move(versionPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GameVersion = ptr.Add(3).Rip().As<const char*>();
			OnlineVersion = ptr.Add(0x47).Add(3).Rip().As<const char*>();
		});

		soup::Range hwndRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern hwndPattern("E8 ? ? ? ? 84 C0 74 25 48 8B 0D");
		batch.Add("HWND", std::move(hwndRange), std::move(hwndPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			Hwnd = ptr.Add(9).Add(3).Rip().As<HWND*>();
		});

		soup::Range screenResRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern screenResPattern("75 39 0F 57 C0 F3 0F 2A 05");
		batch.Add("ScreenRes", std::move(screenResRange), std::move(screenResPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			ScreenResX = ptr.Add(0x9).Rip().As<std::uint32_t*>();
			ScreenResY = ptr.Add(0x22).Rip().As<std::uint32_t*>();
		});

		soup::Range scriptThreadsRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern scriptThreadsPattern("48 8B 05 ? ? ? ? 48 89 34 F8 48 FF C7 48 39 FB 75 97");
		batch.Add("ScriptThreads", std::move(scriptThreadsRange), std::move(scriptThreadsPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			ScriptThreads = ptr.Add(3).Rip().As<rage::atArray<rage::scrThread*>*>();
		});

		soup::Range initNativeTablesRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern initNativeTablesPattern("EB 2A 0F 1F 40 00 48 8B 54 17 10");
		batch.Add("InitNativeTables", std::move(initNativeTablesRange), std::move(initNativeTablesPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			InitNativeTables = ptr.Sub(0x2A).As<PVOID>();
		});

		soup::Range gameLogosRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern gameLogosPattern("70 6C 61 74 66 6F 72 6D 3A 2F 6D 6F 76 69 65 73 2F 72 6F 63");
		batch.Add("GameLogos", std::move(gameLogosRange), std::move(gameLogosPattern), [this](soup::Pointer p) {
			GameLogos = p.as<PVOID>();
		});

		soup::Range scriptProgramsRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern scriptProgramsPattern("48 C7 84 C8 D8 00 00 00 00 00 00 00");
		batch.Add("ScriptPrograms", std::move(scriptProgramsRange), std::move(scriptProgramsPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			ScriptPrograms = ptr.Add(0x13).Add(3).Rip().Add(0xD8).As<rage::scrProgram**>();
		});

		soup::Range swapchainRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern swapchainPattern("72 C7 EB 02 31 C0 8B 0D");
		batch.Add("IDXGISwapChain", std::move(swapchainRange), std::move(swapchainPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			CommandQueue = ptr.Add(0x1A).Add(3).Rip().As<ID3D12CommandQueue**>();
			SwapChain = ptr.Add(0x21).Add(3).Rip().As<IDXGISwapChain1**>();
		});

		soup::Range wndProcRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern wndProcPattern("3D 85 00 00 00 0F 87 2D 02 00 00");
		batch.Add("WndProc", std::move(wndProcRange), std::move(wndProcPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			WndProc = ptr.Sub(0x4F).As<PVOID>();
		});

		soup::Range runScriptThreadsRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern runScriptThreadsPattern("BE 40 5D C6 00");
		batch.Add("RunScriptThreads", std::move(runScriptThreadsRange), std::move(runScriptThreadsPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			RunScriptThreads = ptr.Sub(0xA).As<PVOID>();
		});

		soup::Range handlesAndPtrsRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern handlesAndPtrsPattern("0F 1F 84 00 00 00 00 00 89 F8 0F 28 FE 41");
		batch.Add("HandlesAndPtrs", std::move(handlesAndPtrsRange), std::move(handlesAndPtrsPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			HandleToPtr = ptr.Add(0x21).Add(1).Rip().As<Functions::HandleToPtr>();
			PtrToHandle = ptr.Sub(0xB).Add(1).Rip().As<Functions::PtrToHandle>();
		});

		soup::Range pedFactoryRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern pedFactoryPattern("C7 40 30 03 00 00 00 48 8B 0D");
		batch.Add("PedFactory", std::move(pedFactoryRange), std::move(pedFactoryPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			PedFactory = ptr.Add(7).Add(3).Rip().As<CPedFactory**>();
		});

		soup::Range getNetPlayerFromPIDRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern getNetPlayerFromPIDPattern("83 FB 20 74 2A 89 D9");
		batch.Add("GetNetPlayerFromPID", std::move(getNetPlayerFromPIDRange), std::move(getNetPlayerFromPIDPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GetNetPlayerFromPid = ptr.Add(8).Rip().As<Functions::GetNetPlayerFromPid>();
		});

		soup::Range isSessionStartedRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern isSessionStartedPattern("0F B6 05 ? ? ? ? 0A 05 ? ? ? ? 75 2A");
		batch.Add("IsSessionStarted", std::move(isSessionStartedRange), std::move(isSessionStartedPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			IsSessionStarted = ptr.Add(3).Rip().As<bool*>();
		});

		soup::Range assignPhysicalIndexRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern assignPhysicalIndexPattern("41 8D 47 01 3C 20 0F 87 68 01 00 00");
		batch.Add("AssignPhysicalIndex", std::move(assignPhysicalIndexRange), std::move(assignPhysicalIndexPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			AssignPhysicalIndex = ptr.Sub(0x13).As<PVOID>();
		});

		soup::Range networkPlayerMgrShutdownRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern networkPlayerMgrShutdownPattern("84 C0 0F 84 88 00 00 00 4C 89 F9 E8");
		batch.Add("NetworkPlayerMgrShutdown", std::move(networkPlayerMgrShutdownRange), std::move(networkPlayerMgrShutdownPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			NetworkPlayerMgrShutdown = ptr.Sub(0x1B).As<PVOID>();
		});

		soup::Range scriptGlobalsRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern scriptGlobalsPattern("48 8B 8E B8 00 00 00 48 8D 15 ? ? ? ? 49 89 D8");
		batch.Add("ScriptGlobals", std::move(scriptGlobalsRange), std::move(scriptGlobalsPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			ScriptGlobals = ptr.Add(7).Add(3).Rip().As<std::int64_t**>();
		});

		soup::Range triggerWeaponDamageEventRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern triggerWeaponDamageEventPattern("E8 ? ? ? ? 66 90 FF C5");
		batch.Add("TriggerWeaponDamageEvent", std::move(triggerWeaponDamageEventRange), std::move(triggerWeaponDamageEventPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			TriggerWeaponDamageEvent = ptr.Add(1).Rip().As<Functions::TriggerWeaponDamageEvent>();
		});

		soup::Range regionCodeRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern regionCodePattern("4C 8D 05 ? ? ? ? 48 89 F1 48 89 FA E8 ? ? ? ? 84 C0 74 3D");
		batch.Add("RegionCode", std::move(regionCodeRange), std::move(regionCodePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			RegionCode = ptr.Add(3).Rip().As<int*>();
		});

		soup::Range networkObjectMgrRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern networkObjectMgrPattern("41 83 7E FA 02 40 0F 9C C5 C1 E5 02");
		batch.Add("NetworkObjectMgr&GetSyncTreeForType", std::move(networkObjectMgrRange), std::move(networkObjectMgrPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			NetworkObjectMgr = ptr.Add(0xC).Add(3).Rip().As<CNetworkObjectMgr**>();
			GetSyncTreeForType = ptr.Add(0x13).Add(1).Rip().As<Functions::GetSyncTreeForType>();
		});

		soup::Range writeNodeDataRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern writeNodeDataPattern("48 8B 89 A8 00 00 00 48 8B 01 48 8B 40 10 48 FF E0");
		batch.Add("WriteNodeData", std::move(writeNodeDataRange), std::move(writeNodeDataPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			WriteNodeData = ptr.As<PVOID>();
		});

		soup::Range shouldUseNodeCacheRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern shouldUseNodeCachePattern("83 FA 20 74 1D 48 89 CE");
		batch.Add("ShouldUseNodeCache&Nullsub", std::move(shouldUseNodeCacheRange), std::move(shouldUseNodeCachePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			ShouldUseNodeCache = ptr.Sub(5).As<PVOID>();
			Nullsub = ptr.Add(0x29).As<PVOID>();
		});

		soup::Range isNodeInScopeRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern isNodeInScopePattern("41 83 F9 02 74 22 48 8B 06");
		batch.Add("IsNodeInScope", std::move(isNodeInScopeRange), std::move(isNodeInScopePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			IsNodeInScope = ptr.Sub(0x26).As<PVOID>();
		});

		soup::Range writeSyncTreeRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern writeSyncTreePattern("4D 89 CD 45 89 C6 41 89 D7 48 89 CF 8B 05 ? ? ? ? 65 48 8B 0C 25 58 00 00 00");
		batch.Add("WriteSyncTree", std::move(writeSyncTreeRange), std::move(writeSyncTreePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			WriteSyncTree = ptr.Sub(0x10).As<PVOID>();
		});

		soup::Range migrateObjectRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern migrateObjectPattern("48 8B 96 D0 00 00 00 4C 89 F9 41 B8 03 00 00 00");
		batch.Add("MigrateObject", std::move(migrateObjectRange), std::move(migrateObjectPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			MigrateObject = ptr.Add(0x10).Add(1).Rip().As<Functions::MigrateObject>();
		});

		soup::Range networkPlayerMgrRange2(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern networkPlayerMgrPattern2("75 0E 48 8B 05 ? ? ? ? 48 8B 88 F0 00 00 00");
		batch.Add("NetworkPlayerMgr", std::move(networkPlayerMgrRange2), std::move(networkPlayerMgrPattern2), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			NetworkPlayerMgr = ptr.Add(2).Add(3).Rip().As<CNetworkPlayerMgr**>();
		});

		soup::Range queuePacketRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern queuePacketPattern("45 89 F1 E8 ? ? ? ? 84 C0 74 25");
		batch.Add("QueuePacket", std::move(queuePacketRange), std::move(queuePacketPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			QueuePacket = ptr.Add(3).Add(1).Rip().As<Functions::QueuePacket>();
		});

		soup::Range getNetObjectByIdRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern getNetObjectByIdPattern("0F B7 4E 60 E8");
		batch.Add("GetNetObjectById", std::move(getNetObjectByIdRange), std::move(getNetObjectByIdPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GetNetObjectById = ptr.Add(4).Add(1).Rip().As<Functions::GetNetObjectById>();
		});

		soup::Range requestControlRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern requestControlPattern("74 0A 48 89 F9 E8 ? ? ? ? 31 F6 89 F0 48 83 C4 20");
		batch.Add("RequestControl", std::move(requestControlRange), std::move(requestControlPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			RequestControl = ptr.Add(5).Add(1).Rip().As<Functions::RequestControl>();
		});

		soup::Range spectatePatchRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern spectatePatchPattern("74 ? 66 83 FF 0D");
		batch.Add("SpectatePatch", std::move(spectatePatchRange), std::move(spectatePatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			SpectatePatch = BytePatches::Add(p.as<std::uint8_t*>(), 0xEB);
		});

		// Checked working

		soup::Range writeNetArrayDataRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern writeNetArrayDataPattern("0F 84 06 03 00 00 0F B6 83");
		batch.Add("WriteNetArrayData", std::move(writeNetArrayDataRange), std::move(writeNetArrayDataPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			WriteNetArrayData = ptr.Sub(0x4E).As<PVOID>();
			NetArrayMgr = ptr.Sub(0x32).Add(3).As<rage::netArrayMgr**>();
		});

		soup::Range netArrayCachedDataPatchRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern netArrayCachedDataPatchPattern("0F 84 64 FE FF FF FF");
		batch.Add("NetArrayCachedDataPatch", std::move(netArrayCachedDataPatchRange), std::move(netArrayCachedDataPatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			NetArrayCachedDataPatch = BytePatches::Add(ptr.As<void*>(), std::to_array<std::uint8_t>({0xE9, 0x65, 0xFE, 0xFF, 0xFF, 0x90}));
		});

		soup::Range statsMgrRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern statsMgrPattern("89 6C 24 28 48 8D 0D ? ? ? ? 48 8D");
		batch.Add("CStatsMgr", std::move(statsMgrRange), std::move(statsMgrPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			StatsMgr = ptr.Add(4).Add(3).Rip().As<CStatsMgr*>();
		});

		soup::Range getPackedStatDataRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern getPackedStatDataPattern("8D 81 37 FE FF FF");
		batch.Add("GetPackedStatData", std::move(getPackedStatDataRange), std::move(getPackedStatDataPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GetPackedStatData = ptr.Sub(0xE).As<Functions::GetPackedStatData>();
		});

		soup::Range netCatalogRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern netCatalogPattern("0F 82 55 FF FF FF 44 89 7C 24 30");
		batch.Add("NetCatalog&GetCatalogItem", std::move(netCatalogRange), std::move(netCatalogPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			NetCatalog = ptr.Add(0xB).Add(3).Rip().As<rage::netCatalog*>();
			GetCatalogItem = ptr.Add(0x17).Add(1).Rip().As<Functions::GetCatalogItem>();
		});

		soup::Range transactionMgrRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern transactionMgrPattern("48 8B 05 ? ? ? ? 80 78 39 00 74 2D");
		batch.Add("TransactionMgr", std::move(transactionMgrRange), std::move(transactionMgrPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			TransactionMgr = ptr.Add(3).Rip().As<void**>();
		});

		soup::Range getActiveBasketRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern getActiveBasketPattern("48 8B 40 10 81 7B 0C AE A0 A9 04");
		batch.Add("GetActiveBasket", std::move(getActiveBasketRange), std::move(getActiveBasketPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GetActiveBasket = ptr.Sub(0x39).As<Functions::GetActiveBasket>();
		});

		soup::Range pedPoolRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern pedPoolPattern("80 79 4B 00 0F 84 F5 00 00 00 48 89 F1");
		batch.Add("PedPool", std::move(pedPoolRange), std::move(pedPoolPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			PedPool = ptr.Add(0x18).Add(3).Rip().As<PoolEncryption*>();
		});

		soup::Range vehiclePoolRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern vehiclePoolPattern("48 83 78 18 0D");
		batch.Add("VehiclePool", std::move(vehiclePoolRange), std::move(vehiclePoolPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			VehiclePool = ptr.Sub(0xA).Add(3).Rip().As<rage::fwVehiclePool***>();
		});

		soup::Range objectPoolRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern objectPoolPattern("48 8B 04 0A C3 0F B6 05");
		batch.Add("ObjectPool", std::move(objectPoolRange), std::move(objectPoolPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			ObjectPool = ptr.Add(5).Add(3).Rip().As<PoolEncryption*>();
		});

		soup::Range httpStartRequestRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern httpStartRequestPattern("56 57 48 83 EC 28 48 89 CE 8B 81 ? ? ? ? FF C8 83 F8 04 0F 87");
		batch.Add("HttpStartRequest", std::move(httpStartRequestRange), std::move(httpStartRequestPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			HttpStartRequest = ptr.As<PVOID>();
		});

		soup::Range networkSessionRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern networkSessionPattern("49 C7 86 F8 00 00 00 00 00 00 00 48 8B 05");
		batch.Add("NetworkSession", std::move(networkSessionRange), std::move(networkSessionPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			NetworkSession = ptr.Add(0x17).Add(3).Rip().As<CNetworkSession**>();
		});

		soup::Range joinSessionByInfoRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern joinSessionByInfoPattern("E8 ? ? ? ? 0F 10 87 ? ? ? ? 0F 11 86 ? ? ? ? 88 86 ? ? ? ? 84 C0");
		batch.Add("JoinSessionByInfo", std::move(joinSessionByInfoRange), std::move(joinSessionByInfoPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			JoinSessionByInfo = ptr.Add(1).Rip().As<Functions::JoinSessionByInfo>();
		});

		soup::Range getSessionByGamerHandleRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern getSessionByGamerHandlePattern("48 C7 84 24 80 00 00 00 10 00 00 08");
		batch.Add("GetSessionByGamerHandle", std::move(getSessionByGamerHandleRange), std::move(getSessionByGamerHandlePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GetSessionByGamerHandle = ptr.Sub(0x4A).Add(1).Rip().As<Functions::GetSessionByGamerHandle>();
		});

		soup::Range networkTimeRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern networkTimePattern("89 05 ? ? ? ? 80 3D ? ? ? ? ? 0F 84 ? ? ? ? E9");
		batch.Add("NetworkTime", std::move(networkTimeRange), std::move(networkTimePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			NetworkTime = ptr.Add(2).Rip().As<std::uint32_t*>();
		});

		soup::Range gameTimerRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern gameTimerPattern("3B 2D ? ? ? ? 76 ? 89 D9");
		batch.Add("GameTimer", std::move(gameTimerRange), std::move(gameTimerPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GameTimer = ptr.Add(2).Rip().As<std::uint32_t*>();
		});

		soup::Range queueDependencyRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern queueDependencyPattern("0F 29 46 50 48 8D 05");
		batch.Add("QueueDependency&SigScanMemory", std::move(queueDependencyRange), std::move(queueDependencyPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			QueueDependency = ptr.Add(0x71).Add(1).Rip().As<PVOID>();
			SigScanMemory = ptr.Add(4).Add(3).Rip().As<PVOID>();
		});

		soup::Range scriptVMRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern scriptVMPattern("49 63 41 1C");
		batch.Add("ScriptVM", std::move(scriptVMRange), std::move(scriptVMPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			ScriptVM = ptr.Sub(0x24).As<Functions::ScriptVM>();
		});

		soup::Range prepareMetricForSendingRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern prepareMetricForSendingPattern("41 56 56 57 55 53 48 83 EC ? 4C 89 CB 4C 89 C6");
		batch.Add("PrepareMetricForSending", std::move(prepareMetricForSendingRange), std::move(prepareMetricForSendingPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			PrepareMetricForSending = ptr.As<PVOID>();
		});

		soup::Range beDataRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern beDataPattern("48 C7 05 ? ? ? ? 00 00 00 00 E8 ? ? ? ? 48 89 C1 E8 ? ? ? ? E8 ? ? ? ? BD 0A 00 00 00");
		batch.Add("BEData", std::move(beDataRange), std::move(beDataPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			BERestartStatus = ptr.Add(3).Rip().Add(8).Add(4).As<int*>();
			NeedsBERestart = ptr.Add(3).Rip().Add(8).Add(4).Add(8).As<bool*>();
			IsBEBanned = ptr.Add(3).Rip().Add(8).Add(4).Add(8).Add(4).As<bool*>();
		});

		soup::Range battlEyeStatusUpdatePatchRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern battlEyeStatusUpdatePatchPattern("C6 05 ? ? ? ? 00 84 C0 0F 84 ? ? ? ? E9");
		batch.Add("BattlEyeStatusUpdatePatch", std::move(battlEyeStatusUpdatePatchRange), std::move(battlEyeStatusUpdatePatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			BattlEyeStatusUpdatePatch = BytePatches::Add(ptr.Add(11).Rip().Add(1).Rip().As<void*>(), std::to_array<std::uint8_t>({0xC3}));
		});

		soup::Range statsMpCharacterMappingDataRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern statsMpCharacterMappingDataPattern("48 8D 0D ? ? ? ? 89 F2 0F 28 74 24 ? 48 83 C4 38");
		batch.Add("CStatsMpCharacterMappingData", std::move(statsMpCharacterMappingDataRange), std::move(statsMpCharacterMappingDataPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			StatsMpCharacterMappingData = ptr.Add(3).Rip().As<CStatsMpCharacterMappingData*>();
		});

		soup::Range scMembershipStuffRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern scMembershipStuffPattern("48 8D 15 ? ? ? ? 41 B8 18 02 00 00 E8");
		batch.Add("ScMembershipStuff", std::move(scMembershipStuffRange), std::move(scMembershipStuffPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			HasGTAPlus = ptr.Add(3).Rip().As<int*>();
		});

		soup::Range battlEyeServerProcessPlayerJoinRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern battlEyeServerProcessPlayerJoinPattern("48 89 10 48 89 48 10 89 F9");
		batch.Add("BattlEyeServerProcessPlayerJoin", std::move(battlEyeServerProcessPlayerJoinRange), std::move(battlEyeServerProcessPlayerJoinPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			BattlEyeServerProcessPlayerJoin = ptr.Sub(4).Rip().As<PVOID*>()[1];
		});

		soup::Range getDLCHashRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern getDLCHashPattern("31 D2 E8 ? ? ? ? 3B 84");
		batch.Add("GetDLCHash&DLCManager", std::move(getDLCHashRange), std::move(getDLCHashPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			DLCManager = ptr.Sub(4).Rip().As<void**>();
			GetDLCHash = ptr.Add(3).Rip().As<PVOID>();
		});

		soup::Range gameDataHashRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern gameDataHashPattern("48 8D 3D ? ? ? ? 69 C9");
		batch.Add("GameDataHash", std::move(gameDataHashRange), std::move(gameDataHashPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GameDataHash = ptr.Add(3).Rip().As<CGameDataHash*>();
		});

		soup::Range assistedAimShouldReleaseEntityRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern assistedAimShouldReleaseEntityPattern("80 7F 28 04 75 6A");
		batch.Add("AssistedAimShouldReleaseEntity", std::move(assistedAimShouldReleaseEntityRange), std::move(assistedAimShouldReleaseEntityPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			AssistedAimShouldReleaseEntity = ptr.Sub(0xF).As<PVOID>();
		});

		soup::Range assistedAimFindNewTargetRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern assistedAimFindNewTargetPattern("0F 84 C9 00 00 00 48 89 CE 48 89 F9");
		batch.Add("AssistedAimFindNewTarget", std::move(assistedAimFindNewTargetRange), std::move(assistedAimFindNewTargetPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			AssistedAimFindNewTarget = ptr.Sub(0x33).As<Functions::AssistedAimFindNewTarget>();
		});

		soup::Range anticheatInitializedHashRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern anticheatInitializedHashPattern("89 9E C8 00 00 00 48 8B 0D ? ? ? ? 48 85 C9 74 46");
		batch.Add("InitializedHash-Anticheat&GetAnticheat", std::move(anticheatInitializedHashRange), std::move(anticheatInitializedHashPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			AnticheatInitializedHash = ptr.Add(9).Rip().As<rage::Obf32**>();
			GetAnticheatInitializedHash = ptr.Add(0x13).Rip().As<PVOID>();
		});

		soup::Range anticheatContextRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern anticheatContextPattern("48 8D BB 70 0A 00 00 4C 8D 35 ? ? ? ? 66 90");
		batch.Add("AnticheatContext", std::move(anticheatContextRange), std::move(anticheatContextPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			AnticheatContext = ptr.Sub(0x12).Add(3).Rip().As<CAnticheatContext**>();
		});

		soup::Range getAnticheatInitializedHash2Range(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern getAnticheatInitializedHash2Pattern("89 9E E8 00 00 00 89 C2 E8 ? ? ? ? 69");
		batch.Add("GetAnticheatInitializedHash2", std::move(getAnticheatInitializedHash2Range), std::move(getAnticheatInitializedHash2Pattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GetAnticheatInitializedHash2 = ptr.Add(0x9).Rip().As<PVOID>();
		});

		soup::Range abilityBarPatchRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern abilityBarPatchPattern("75 39 48 85 F6 74 1A 48 89 F1 E8");
		batch.Add("AbilityBarPatch", std::move(abilityBarPatchRange), std::move(abilityBarPatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			AbilityBarPatch = BytePatches::Add(ptr.As<std::uint16_t*>(), 0x9090);
		});

		soup::Range matchmakingAdvertiseRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern matchmakingAdvertisePattern("C7 47 30 01 00 00 00 E9 92");
		batch.Add("MatchmakingAdvertise", std::move(matchmakingAdvertiseRange), std::move(matchmakingAdvertisePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			MatchmakingAdvertise = ptr.Sub(0xC).Rip().As<PVOID>();
		});

		soup::Range matchmakingUpdateRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern matchmakingUpdatePattern("C7 47 30 02 00 00 00 EB 7A");
		batch.Add("MatchmakingUpdate", std::move(matchmakingUpdateRange), std::move(matchmakingUpdatePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			MatchmakingUpdate = ptr.Sub(0x8).Rip().As<PVOID>();
		});

		soup::Range matchmakingUnadvertiseRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern matchmakingUnadvertisePattern("C7 86 C8 01 00 00 04 00 00 00");
		batch.Add("MatchmakingUnadvertise", std::move(matchmakingUnadvertiseRange), std::move(matchmakingUnadvertisePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			MatchmakingUnadvertise = ptr.Sub(0xC).Rip().As<PVOID>();
		});

		soup::Range matchmakingSessionDetailSendResponseRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern matchmakingSessionDetailSendResponsePattern("48 B8 01 00 00 00 0D 00 00 00");
		batch.Add("SessionDetailSendResponse", std::move(matchmakingSessionDetailSendResponseRange), std::move(matchmakingSessionDetailSendResponsePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			MatchmakingSessionDetailSendResponse = ptr.Add(0x2F).Rip().As<PVOID>();
		});

		soup::Range gameSkeletonUpdateRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern gameSkeletonUpdatePattern("56 48 83 EC 20 48 8B 81 40 01 00 00 48 85 C0");
		batch.Add("GameSkeletonUpdate", std::move(gameSkeletonUpdateRange), std::move(gameSkeletonUpdatePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GameSkeletonUpdate = ptr.As<PVOID>();
		});

		soup::Range modelSpawnBypassRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern modelSpawnBypassPattern("E8 ? ? ? ? 48 8B 78 48");
		batch.Add("ModelSpawnBypass", std::move(modelSpawnBypassRange), std::move(modelSpawnBypassPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			ModelSpawnBypass = BytePatches::Add(ptr.Add(1).Rip().Add(0x2B).As<std::uint8_t*>(), 0xEB);
		});

		soup::Range worldModelSpawnBypassRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern worldModelSpawnBypassPattern("4C 8B 2C 01 4D 85 ED 0F 84 ? ? ? ?");
		batch.Add("WorldModelSpawnBypass", std::move(worldModelSpawnBypassRange), std::move(worldModelSpawnBypassPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			WorldModelSpawnBypass = BytePatches::Add(ptr.Add(4).As<void*>(), std::to_array<std::uint8_t>({0xEB, 0x12, 0x90}));
		});

		soup::Range receiveNetMessageRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern receiveNetMessagePattern("48 81 C1 00 03 00 00 4C 89 E2");
		batch.Add("ReceiveNetMessage", std::move(receiveNetMessageRange), std::move(receiveNetMessagePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			ReceiveNetMessage = ptr.Add(0xD).Add(1).Rip().As<PVOID>();
		});

		soup::Range netEventMgrRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern netEventMgrPattern("4C 8B 05 ? ? ? ? 44 0F B7 CA");
		batch.Add("NetEventMgr", std::move(netEventMgrRange), std::move(netEventMgrPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			NetEventMgr = ptr.Add(3).Rip().As<rage::netEventMgr**>();
		});

		soup::Range sendEventAckRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern sendEventAckPattern("E8 ? ? ? ? 84 C0 75 ? 44 89 F5");
		batch.Add("SendEventAck", std::move(sendEventAckRange), std::move(sendEventAckPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			EventAck = ptr.Add(1).Rip().As<Functions::EventAck>();
			SendEventAck = ptr.Add(0x1A).Add(1).Rip().As<Functions::SendEventAck>();
		});

		soup::Range formatIntCaller1Range(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern formatIntCaller1Pattern("48 89 35 ? ? ? ? 48 8B 74 24");
		batch.Add("FormatIntCaller1", std::move(formatIntCaller1Range), std::move(formatIntCaller1Pattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			FormatIntCaller1 = ptr.Add(0x5D).As<PVOID>();
		});

		soup::Range formatIntCaller2Range(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern formatIntCaller2Pattern("48 B8 20 73 69 7A 65 3D 27 32 48 89 84 24");
		batch.Add("FormatIntCaller2", std::move(formatIntCaller2Range), std::move(formatIntCaller2Pattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			FormatIntCaller2 = ptr.Sub(0x11).As<PVOID>();
		});

		soup::Range shouldTargetEntityPatchRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern shouldTargetEntityPatchPattern("F6 80 A9 14 00 00 01");
		batch.Add("ShouldNotTargetEntityPatch", std::move(shouldTargetEntityPatchRange), std::move(shouldTargetEntityPatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			ShouldNotTargetEntityPatch = BytePatches::Add(ptr.Sub(0x53).As<void*>(), std::to_array<std::uint8_t>({0xB0, 0x00, 0xC3}));
		});

		soup::Range getAssistedAimTypePatchRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern getAssistedAimTypePatchPattern("FF E0 48 8D 86");
		batch.Add("GetAssistedAimTypePatch", std::move(getAssistedAimTypePatchRange), std::move(getAssistedAimTypePatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GetAssistedAimTypePatch = BytePatches::Add(ptr.Sub(0x15).As<void*>(), std::to_array<std::uint8_t>({0xBD, 0x01, 0x00, 0x00, 0x00}));
		});

		soup::Range getLockOnPosPatchRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern getLockOnPosPatchPattern("0F 29 74 24 ? 48 89 D6 48 89 CF 48 8B 05");
		batch.Add("GetLockOnPosPatch", std::move(getLockOnPosPatchRange), std::move(getLockOnPosPatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GetLockOnPosPatch = BytePatches::Add(ptr.Add(0x22).As<std::uint8_t*>(), 0xEB);
		});

		soup::Range shouldAllowDriverLockOnPatchRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern shouldAllowDriverLockOnPatchPattern("75 ? 45 89 C7 49 89 CE");
		batch.Add("ShouldAllowDriverLockOnPatch", std::move(shouldAllowDriverLockOnPatchRange), std::move(shouldAllowDriverLockOnPatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			ShouldAllowDriverLockOnPatch = BytePatches::Add(ptr.Sub(0x2C).As<std::uint8_t*>(), std::to_array<std::uint8_t>({0xB0, 0x01, 0xC3}));
		});

		soup::Range allowPausingInSessionPatchRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern allowPausingInSessionPatchPattern("80 88 ? ? ? ? ? EB ? E8");
		batch.Add("AllowPausingInSessionPatch", std::move(allowPausingInSessionPatchRange), std::move(allowPausingInSessionPatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			AllowPausingInSessionPatch = BytePatches::Add(ptr.Sub(0x1E).As<std::uint8_t*>(), 0xEB);
		});

		soup::Range getPoolTypeRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern getPoolTypePattern("BA CE 94 A6 ED E8");
		batch.Add("GetPoolType", std::move(getPoolTypeRange), std::move(getPoolTypePattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GetPoolType = ptr.Sub(19).As<PVOID>();
		});

		soup::Range setJoinRequestPoolTypePatchRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern setJoinRequestPoolTypePatchPattern("89 86 ? ? ? ? E8 ? ? ? ? 89 C0");
		batch.Add("SetJoinRequestPoolTypePatch", std::move(setJoinRequestPoolTypePatchRange), std::move(setJoinRequestPoolTypePatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			SetJoinRequestPoolTypePatch = BytePatches::Add(ptr.Sub(5).As<std::uint8_t*>(), std::to_array<std::uint8_t>({0xB8, 0x00, 0x00, 0x00, 0x00}));
		});

		soup::Range handleJoinRequestIgnorePoolPatchRange(reinterpret_cast<void*>(gta5->Base()), gta5->Size());
		soup::Pattern handleJoinRequestIgnorePoolPatchPattern("41 83 FF 05 0F 84 ? ? ? ? 8B 84 F7");
		batch.Add("HandleJoinRequestIgnorePoolPatch", std::move(handleJoinRequestIgnorePoolPatchRange), std::move(handleJoinRequestIgnorePoolPatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			HandleJoinRequestIgnorePoolPatch = BytePatches::Add(ptr.As<void*>(), std::to_array<std::uint8_t>({0x39, 0xC9, 0x90, 0x90}));
		});


		if (!batch.Run())
		{
			LOG(FATAL) << "Failed to initialize pointer patterns";
			return false;
		}

		return true;
	}

	bool Pointers::LateInit()
	{
		auto sc = g_ModuleMgr.Get("socialclub.dll"_J);
		while (!sc)
		{
			LOG(WARNING) << "Waiting for socialclub.dll";
			std::this_thread::sleep_for(5s);

			if (IsSocialClubNeverGoingToLoad())
			{
				LOG(WARNING) << "Timed out checking for socialclub.dll";
				return false;
			}

			g_ModuleMgr.LoadModules();
			sc = g_ModuleMgr.Get("socialclub.dll"_J);
		}

		std::unordered_map<std::string, std::uintptr_t> patternBatchCache;
		PatternBatch batch(&patternBatchCache);

		soup::Range getPresenceAttributesRange(reinterpret_cast<void*>(sc->Base()), sc->Size());
		soup::Pattern getPresenceAttributesPattern("48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 40 33 DB 49");
		batch.Add("GetPresenceAttributes", std::move(getPresenceAttributesRange), std::move(getPresenceAttributesPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GetPresenceAttributes = ptr.As<Functions::GetPresenceAttributes>();
		});

		soup::Range numHandlesPatchRange(reinterpret_cast<void*>(sc->Base()), sc->Size());
		soup::Pattern numHandlesPatchPattern("83 FD 20 0F 87 54 02 00 00");
		batch.Add("NumHandlesPatch", std::move(numHandlesPatchRange), std::move(numHandlesPatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			BytePatches::Add(ptr.Add(2).As<std::uint8_t*>(), 100)->Apply();
		});

		soup::Range readAttributePatchRange(reinterpret_cast<void*>(sc->Base()), sc->Size());
		soup::Pattern readAttributePatchPattern("75 70 EB 23");
		batch.Add("ReadAttributesPatch", std::move(readAttributePatchRange), std::move(readAttributePatchPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			BytePatches::Add(ptr.As<void*>(), std::array<std::uint8_t, 2>{0x90, 0x90})->Apply();
		});

		soup::Range readAttributePatch2Range(reinterpret_cast<void*>(sc->Base()), sc->Size());
		soup::Pattern readAttributePatch2Pattern("32 C0 EB ? C7 83");
		batch.Add("ReadAttributesPatch2", std::move(readAttributePatch2Range), std::move(readAttributePatch2Pattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			BytePatches::Add(ptr.As<void*>(), std::array<std::uint8_t, 2>{0xB0, 0x01})->Apply();
		});

		soup::Range getAvatarsRange(reinterpret_cast<void*>(sc->Base()), sc->Size());
		soup::Pattern getAvatarsPattern("89 4B ? 48 8B CB E8 ? ? ? ? 84 C0");
		batch.Add("GetAvatars", std::move(getAvatarsRange), std::move(getAvatarsPattern), [this](soup::Pointer p) {
			PointerCalculator ptr(p.as<std::uintptr_t>());
			GetAvatars = ptr.Add(6).Add(1).Rip().As<Functions::GetAvatars>();
		});

		if (!batch.Run())
		{
			LOG(WARNING) << "Some Social Club patterns could not be found";
			return false;
		}
		return true;
	}
}