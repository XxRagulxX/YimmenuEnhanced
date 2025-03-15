#include "Pointers.hpp"

#include "core/backend/PatternCache.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/memory/PatternScanner.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu
{
	bool Pointers::Init()
	{
		PatternCache::Init();

		const auto gta5 = ModuleMgr.Get("GTA5_Enhanced.exe"_J);
		if (!gta5)
		{
			LOG(FATAL) << "Could not find GTA5_Enhanced.exe, is this GTA 5 Enhanced?";
			return false;
		}

		auto scanner = PatternScanner(gta5);

		constexpr auto swapchainPtrn = Pattern<"72 C7 EB 02 31 C0 8B 0D">("IDXGISwapChain");
		scanner.Add(swapchainPtrn, [this](PointerCalculator ptr) {
			CommandQueue = ptr.Add(0x1A).Add(3).Rip().As<ID3D12CommandQueue**>();
			SwapChain = ptr.Add(0x21).Add(3).Rip().As<IDXGISwapChain1**>();
		});

		constexpr auto wndProcPtrn = Pattern<"3D 85 00 00 00 0F 87 2D 02 00 00">("WndProc");
		scanner.Add(wndProcPtrn, [this](PointerCalculator ptr) {
			WndProc = ptr.Sub(0x4F).As<PVOID>();
		});

		constexpr auto hWndPtrn = Pattern<"E8 ? ? ? ? 84 C0 74 25 48 8B 0D">("HWND");
		scanner.Add(hWndPtrn, [this](PointerCalculator ptr) {
			Hwnd = ptr.Add(9).Add(3).Rip().As<HWND*>();
		});

		constexpr auto screenResPtrn = Pattern<"75 39 0F 57 C0 F3 0F 2A 05">("ScreenRes");
		scanner.Add(screenResPtrn, [this](PointerCalculator ptr) {
			ScreenResX = ptr.Add(0x5).Add(4).Rip().As<std::uint32_t*>();
			ScreenResY = ptr.Add(0x1E).Add(4).Rip().As<std::uint32_t*>();
		});

		constexpr auto scriptThreadsPtrn = Pattern<"48 8B 05 ? ? ? ? 48 89 34 F8 48 FF C7 48 39 FB 75 97">("ScriptThreads");
		scanner.Add(scriptThreadsPtrn, [this](PointerCalculator ptr) {
			ScriptThreads = ptr.Add(3).Rip().As<rage::atArray<rage::scrThread*>*>();
		});

		constexpr auto populateNativesPtrn = Pattern<"EB 2A 0F 1F 40 00 48 8B 54 17 10">("PopulateNatives");
		scanner.Add(populateNativesPtrn, [this](PointerCalculator ptr) {
			PopulateNatives = ptr.Sub(0x2A).As<Functions::PopulateNatives>();
		});

		constexpr auto runScriptThreadsPtrn = Pattern<"BE 40 5D C6 00">("RunScriptThreads");
		scanner.Add(runScriptThreadsPtrn, [this](PointerCalculator ptr) {
			RunScriptThreads = ptr.Sub(0xA).As<PVOID>();
		});

		constexpr auto handlesAndPtrsPtrn = Pattern<"0F 1F 84 00 00 00 00 00 89 F8 0F 28 FE">("HandlesAndPtrs");
		scanner.Add(handlesAndPtrsPtrn, [this](PointerCalculator ptr) {
			HandleToPtr = ptr.Add(0x21).Add(3).Rip().As<Functions::HandleToPtr>();
			PtrToHandle = ptr.Sub(0xB).Add(3).Rip().As<Functions::PtrToHandle>();
		});

		constexpr auto pedFactoryPtrn = Pattern<"C7 40 30 03 00 00 00 48 8B 0D">("PedFactory");
		scanner.Add(pedFactoryPtrn, [this](PointerCalculator ptr) {
			PedFactory = ptr.Add(7).Add(3).Rip().As<CPedFactory**>();
		});

		constexpr auto getNetPlayerFromPidPtrn = Pattern<"83 FB 20 74 2A 89 D9">("GetNetPlayerFromPID");
		scanner.Add(getNetPlayerFromPidPtrn, [this](PointerCalculator ptr) {
			GetNetPlayerFromPid = ptr.Add(8).Rip().As<Functions::GetNetPlayerFromPid>();
		});

		constexpr auto isSessionStarted = Pattern<"0F B6 05 ? ? ? ? 0A 05 ? ? ? ? 75 2A">("IsSessionStarted");
		scanner.Add(isSessionStarted, [this](PointerCalculator addr) {
			IsSessionStarted = addr.Add(3).Rip().As<bool*>();
		});

		constexpr auto assignPhysicalIndexPtrn = Pattern<"41 8D 47 01 3C 20 0F 87 68 01 00 00">("AssignPhysicalIndex");
		scanner.Add(assignPhysicalIndexPtrn, [this](PointerCalculator ptr) {
			AssignPhysicalIndex = ptr.Sub(0x13).As<PVOID>();
		});

		if (!scanner.Scan())
		{
			LOG(FATAL) << "Some patterns could not be found, unloading.";
			return false;
		}

		PatternCache::Update();
		return true;
	}
}