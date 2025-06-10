#include "core/commands/BoolCommand.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	static void SetScriptRouterLinkHook(rage::scrNativeCallContext* ctx);

	class DisableLandingPageBail : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		std::vector<ScriptPatch> m_DoTransitionPatches;

		constexpr static auto m_Scripts = std::to_array({
			"creator"_J,
			"ingamehud"_J,
			"main_persistent"_J,
			"maintransition"_J,
			"selector"_J
		});

		virtual void OnEnable() override
		{
			if (m_DoTransitionPatches.empty())
			{
				for (auto script : m_Scripts)
				{
					// TODO: this doesn't work very well
					m_DoTransitionPatches.push_back(ScriptPatches::AddPatch(script, ScriptPointer("DoTransitionPatch1", "2C 01 ? ? 06 39 06 55 41").Sub(21).Add(8), {0x00, 0x00, 0x55}));
					m_DoTransitionPatches.push_back(ScriptPatches::AddPatch(script, ScriptPointer("DoTransitionPatch2", "2C 01 ? ? 06 39 06 55 41").Add(10), {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55}));
				}
			}

			for (auto script : m_Scripts)
			{
				NativeHooks::AddHook(script, NativeIndex::SET_SCRIPT_ROUTER_LINK, &SetScriptRouterLinkHook);
			}

			for (auto& patch : m_DoTransitionPatches)
			{
				patch->Enable();
			}
		}


		virtual void OnDisable() override
		{
			for (auto& patch : m_DoTransitionPatches)
			{
				patch->Disable();
			}
		}
	};

	static DisableLandingPageBail _DisableLandingPageBail{"disablelandingpagebail", "Disable Landing Page Bail", "Redirect all bails to singleplayer instead of the landing page"};

	static void SetScriptRouterLinkHook(rage::scrNativeCallContext* ctx)
	{
		auto data = ctx->GetArg<std::uint64_t*>(0);

		if (_DisableLandingPageBail.GetState() && data[0] == 3 && data[1] == 5 && data[2] == 11)
		{
			auto script = SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME();
		
			ScriptFunction doTransition(script, ScriptPointer("DoTransition", "2C 01 ? ? 06 39 06 55 41").Sub(21));
			doTransition.Call<void>(58, UINT_MAX, 32);

			ctx->SetReturnValue(TRUE);
		}
		else
		{
			ctx->SetReturnValue(MISC::SET_SCRIPT_ROUTER_LINK(data));
		}
	}
}