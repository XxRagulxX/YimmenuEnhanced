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
			WndProc = ptr.Sub(0x4F).As<WNDPROC>();
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

#if 0
		constexpr auto nativeHandlersPtrn = Pattern<"48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A">("NativeHandlers");
		scanner.Add(nativeHandlersPtrn, [this](PointerCalculator ptr) {
			NativeRegistrationTable = ptr.Add(3).Rip().As<void*>();
			GetNativeHandler        = ptr.Add(12).Rip().As<Functions::GetNativeHandler>();
		});

		constexpr auto fixVectorsPtrn = Pattern<"83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA">("FixVectors");
		scanner.Add(fixVectorsPtrn, [this](PointerCalculator ptr) {
			FixVectors = ptr.As<Functions::FixVectors>();
		});
#endif

		if (!scanner.Scan())
		{
			LOG(FATAL) << "Some patterns could not be found, unloading.";

			return false;
		}

		return true;
	}
}