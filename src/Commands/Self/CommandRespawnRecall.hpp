#pragma once
#include "Commands/Widgets/CommandTickDispatch.hpp"
#include "Commands/Widgets/CommandToggle.hpp"

#include "Core/Pointers.hpp"
#include "Scripting/Natives.hpp"
#include "World/Self.hpp"

namespace Stand
{
	class CommandRespawnRecall : public CommandToggle
	{
	public:
		explicit CommandRespawnRecall(CommandList* parent) :
		    CommandToggle(parent, LIT("Respawn Recall"), CMDNAMES("respawnrecall"))
		{
		}

		void onEnable(Click& click) override
		{
			m_HasDeathPos = false;
			CommandTickDispatch::AddCommand(this);
		}

		void onDisable(Click& click) override
		{
			CommandTickDispatch::RemoveCommand(this);
		}

		void onTick() override
		{
			auto ped = Stand::Self::GetPed();
			if (!ped)
				return;

			if (!m_HasDeathPos)
			{
				if (ped.IsDead())
				{
					m_DeathPos = ped.GetPosition();
					m_HasDeathPos = true;
				}
				return;
			}

			if (!ped.IsDead() && (CAM::IS_SCREEN_FADED_IN() || *Pointers.IsSessionStarted))
			{
				ped.SetPosition(m_DeathPos);
				m_HasDeathPos = false;
			}
		}

		~CommandRespawnRecall() override
		{
			CommandTickDispatch::RemoveCommand(this);
		}

	private:
		rage::fvector3 m_DeathPos{};
		bool m_HasDeathPos = false;
	};
}

namespace Stand::Features
{
	Stand::CommandRespawnRecall& GetCommandRespawnRecall();
}
