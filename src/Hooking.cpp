#include "Hooking.hpp"

#include "BaseHook.hpp"
#include "DetourHook.hpp"
#include "Hooks.hpp"
#include "Pointers.hpp"

namespace YimMenu
{
	Hooking::Hooking()
	{
		// Window hooks

		auto* hook = AddHook("WndProc", Pointers.WndProc, reinterpret_cast<void*>(Hooks::Window::WndProc));
		BaseHook::Add<Hooks::Window::WndProc>(hook);

		// Raw input hooks

		auto* rawInputHook = AddHook("GetRawInputData", reinterpret_cast<void*>(GetProcAddress(LoadLibraryA("user32.dll"), "GetRawInputData")), reinterpret_cast<void*>(Hooks::RawInput::GetRawInputData));
		BaseHook::Add<Hooks::RawInput::GetRawInputData>(rawInputHook);

		// DXGI hooks

		auto swapchain_vft = *reinterpret_cast<void***>(*Pointers.SwapChain);

		auto* presentHook = AddHook("Present", swapchain_vft[Hooks::SwapChain::VMTPresentIdx], reinterpret_cast<void*>(Hooks::SwapChain::Present));
		BaseHook::Add<Hooks::SwapChain::Present>(presentHook);

		auto* resizeBuffersHook = AddHook("ResizeBuffers", swapchain_vft[Hooks::SwapChain::VMTResizeBuffersIdx], reinterpret_cast<void*>(Hooks::SwapChain::ResizeBuffers));
		BaseHook::Add<Hooks::SwapChain::ResizeBuffers>(resizeBuffersHook);


		// Anticheat hooks

		auto* gameSkeletonUpdateHook = AddHook("GameSkeletonUpdate", Pointers.GameSkeletonUpdate, reinterpret_cast<void*>(Hooks::Anticheat::GameSkeletonUpdate));
		BaseHook::Add<Hooks::Anticheat::GameSkeletonUpdate>(gameSkeletonUpdateHook);


		auto* prepareMetricForSendingHook = AddHook("PrepareMetricForSending", Pointers.PrepareMetricForSending, reinterpret_cast<void*>(Hooks::Anticheat::PrepareMetricForSending));
		BaseHook::Add<Hooks::Anticheat::PrepareMetricForSending>(prepareMetricForSendingHook);


		auto* getThreadContextHook = AddHook("GetThreadContext", reinterpret_cast<void*>(GetProcAddress(LoadLibraryA("kernel32.dll"), "GetThreadContext")), reinterpret_cast<void*>(Hooks::Anticheat::GetThreadContext));
		BaseHook::Add<Hooks::Anticheat::GetThreadContext>(getThreadContextHook);

		auto* httpStartRequestHook = AddHook("HttpStartRequest", Pointers.HttpStartRequest, reinterpret_cast<void*>(Hooks::Anticheat::HttpStartRequest));
		BaseHook::Add<Hooks::Anticheat::HttpStartRequest>(httpStartRequestHook);


		auto* battlEyeServerProcessPlayerJoinHook = AddHook("BattlEyeServerProcessPlayerJoin", Pointers.BattlEyeServerProcessPlayerJoin, reinterpret_cast<void*>(Hooks::Anticheat::BattlEyeServerProcessPlayerJoin));
		BaseHook::Add<Hooks::Anticheat::BattlEyeServerProcessPlayerJoin>(battlEyeServerProcessPlayerJoinHook);


		auto* getAnticheatInitializedHashHook = AddHook("GetAnticheatInitializedHash", Pointers.GetAnticheatInitializedHash, reinterpret_cast<void*>(Hooks::Anticheat::GetAnticheatInitializedHash));
		BaseHook::Add<Hooks::Anticheat::GetAnticheatInitializedHash>(getAnticheatInitializedHashHook);


		auto* getAnticheatInitializedHash2Hook = AddHook("GetAnticheatInitializedHash2", Pointers.GetAnticheatInitializedHash2, reinterpret_cast<void*>(Hooks::Anticheat::GetAnticheatInitializedHash2));
		BaseHook::Add<Hooks::Anticheat::GetAnticheatInitializedHash2>(getAnticheatInitializedHash2Hook);

		// Script hooks

		auto* runScriptThreadsHook = AddHook("RunScriptThreads", Pointers.RunScriptThreads, reinterpret_cast<void*>(Hooks::Script::RunScriptThreads));
		BaseHook::Add<Hooks::Script::RunScriptThreads>(runScriptThreadsHook);

		auto* initNativeTablesHook = AddHook("InitNativeTables", Pointers.InitNativeTables, reinterpret_cast<void*>(Hooks::Script::InitNativeTables));
		BaseHook::Add<Hooks::Script::InitNativeTables>(initNativeTablesHook);

		auto* scriptVMHook = AddHook("ScriptVM", reinterpret_cast<void*>(Pointers.ScriptVM), reinterpret_cast<void*>(Hooks::Script::ScriptVM));
		BaseHook::Add<Hooks::Script::ScriptVM>(scriptVMHook);

		auto* assignPhysicalIndexHook = AddHook("AssignPhysicalIndex", Pointers.AssignPhysicalIndex, reinterpret_cast<void*>(Hooks::Info::AssignPhysicalIndex));
		BaseHook::Add<Hooks::Info::AssignPhysicalIndex>(assignPhysicalIndexHook);

		auto* networkPlayerMgrShutdownHook = AddHook("NetworkPlayerMgrShutdown", Pointers.NetworkPlayerMgrShutdown, reinterpret_cast<void*>(Hooks::Info::NetworkPlayerMgrShutdown));
		BaseHook::Add<Hooks::Info::NetworkPlayerMgrShutdown>(networkPlayerMgrShutdownHook);

		// Spoofing hooks

		auto* isNodeInScopeHook = AddHook("IsNodeInScope", Pointers.IsNodeInScope, reinterpret_cast<void*>(Hooks::Spoofing::IsNodeInScope));
		BaseHook::Add<Hooks::Spoofing::IsNodeInScope>(isNodeInScopeHook);

		auto* shouldUseNodeCacheHook = AddHook("ShouldUseNodeCache", Pointers.ShouldUseNodeCache, reinterpret_cast<void*>(Hooks::Spoofing::ShouldUseNodeCache));
		BaseHook::Add<Hooks::Spoofing::ShouldUseNodeCache>(shouldUseNodeCacheHook);

		auto* writeNetArrayDataHook = AddHook("WriteNetArrayData", Pointers.WriteNetArrayData, reinterpret_cast<void*>(Hooks::Spoofing::WriteNetArrayData));
		BaseHook::Add<Hooks::Spoofing::WriteNetArrayData>(writeNetArrayDataHook);

		auto* writeNodeDataHook = AddHook("WriteNodeData", Pointers.WriteNodeData, reinterpret_cast<void*>(Hooks::Spoofing::WriteNodeData));
		BaseHook::Add<Hooks::Spoofing::WriteNodeData>(writeNodeDataHook);

		auto* writeSyncTreeHook = AddHook("WriteSyncTree", Pointers.WriteSyncTree, reinterpret_cast<void*>(Hooks::Spoofing::WriteSyncTree));
		BaseHook::Add<Hooks::Spoofing::WriteSyncTree>(writeSyncTreeHook);

		// Network hooks

		auto* receiveNetMessageHook = AddHook("ReceiveNetMessage", Pointers.ReceiveNetMessage, reinterpret_cast<void*>(Hooks::Network::ReceiveNetMessage));
		BaseHook::Add<Hooks::Network::ReceiveNetMessage>(receiveNetMessageHook);

		auto* getPoolTypeHook = AddHook("GetPoolType", Pointers.GetPoolType, reinterpret_cast<void*>(Hooks::Network::GetPoolType));
		BaseHook::Add<Hooks::Network::GetPoolType>(getPoolTypeHook);

		auto* getDLCHashHook = AddHook("GetDLCHash", Pointers.GetDLCHash, reinterpret_cast<void*>(Hooks::Network::GetDLCHash));
		BaseHook::Add<Hooks::Network::GetDLCHash>(getDLCHashHook);

		// Matchmaking hooks

		auto* matchmakingAdvertiseHook = AddHook("MatchmakingAdvertise", Pointers.MatchmakingAdvertise, reinterpret_cast<void*>(Hooks::Matchmaking::MatchmakingAdvertise));
		BaseHook::Add<Hooks::Matchmaking::MatchmakingAdvertise>(matchmakingAdvertiseHook);


		auto* matchmakingSessionDetailSendResponseHook = AddHook("MatchmakingSessionDetailSendResponse", Pointers.MatchmakingSessionDetailSendResponse, reinterpret_cast<void*>(Hooks::Matchmaking::MatchmakingSessionDetailSendResponse));
		BaseHook::Add<Hooks::Matchmaking::MatchmakingSessionDetailSendResponse>(matchmakingSessionDetailSendResponseHook);

		auto* matchmakingUnadvertiseHook = AddHook("MatchmakingUnadvertise", Pointers.MatchmakingUnadvertise, reinterpret_cast<void*>(Hooks::Matchmaking::MatchmakingUnadvertise));
		BaseHook::Add<Hooks::Matchmaking::MatchmakingUnadvertise>(matchmakingUnadvertiseHook);

		auto* matchmakingUpdateHook = AddHook("MatchmakingUpdate", Pointers.MatchmakingUpdate, reinterpret_cast<void*>(Hooks::Matchmaking::MatchmakingUpdate));
		BaseHook::Add<Hooks::Matchmaking::MatchmakingUpdate>(matchmakingUpdateHook);

		// Misc hooks

		auto* assistedAimShouldReleaseEntityHook = AddHook("AssistedAimShouldReleaseEntity", Pointers.AssistedAimShouldReleaseEntity, reinterpret_cast<void*>(Hooks::Misc::AssistedAimShouldReleaseEntity));
		BaseHook::Add<Hooks::Misc::AssistedAimShouldReleaseEntity>(assistedAimShouldReleaseEntityHook);

	}

	Hooking::~Hooking()
	{
		DestroyImpl();
	}

	bool Hooking::Init()
	{
		return GetInstance().InitImpl();
	}

	void Hooking::Destroy()
	{
		GetInstance().DestroyImpl();
		BytePatches::RestoreAll();
	}

	bool Hooking::InitImpl()
	{
		for (auto& hook : m_Hooks)
			hook->Enable();

		m_MinHook.ApplyQueued();

		return true;
	}

	void Hooking::DestroyImpl()
	{
		for (auto& hook : m_Hooks)
			hook->Disable();

		m_MinHook.ApplyQueued();

		m_Hooks.clear(); // unique_ptr calls DetourHook destructor
	}

	DetourHook* Hooking::AddHook(
	    std::string_view name,
	    void* target,
	    void* detour)
	{
		auto hook = std::make_unique<DetourHook>(
		    name,
		    target,
		    detour);

		auto* ptr = hook.get();

		m_Hooks.emplace_back(std::move(hook));

		return ptr;
	}
}