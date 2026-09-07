#pragma once
#include "Commands/Self/CommandGrace.hpp"
#include "Commands/Widgets/CommandTickDispatch.hpp"
#include "Commands/Widgets/CommandToggle.hpp"

#include "Rendering/Notifications.hpp"
#include "Scripting/Natives.hpp"
#include "World/Self.hpp"

#include <chrono>

namespace Stand
{
	class CommandClumsiness : public CommandToggle
	{
	public:
		explicit CommandClumsiness(CommandList* parent, CommandGrace* grace) :
		    CommandToggle(parent, LIT("Clumsiness"), CMDNAMES("clumsiness", "clumsyness"), LIT("Makes you ragdoll on collisions")),
		    m_Grace(grace)
		{
		}

		void onEnable(Click& click) override
		{
			if (m_Grace->m_on)
			{
				Notifications::Show("Clumsiness",
				    "Gracefulness (No Ragdoll) is on - Clumsiness won't work until it's off.",
				    NotificationType::Warning);
			}

			m_ReenableAt = {};
			CommandTickDispatch::AddCommand(this);
		}

		void onDisable(Click& click) override
		{
			CommandTickDispatch::RemoveCommand(this);

			if (auto ped = Stand::Self::GetPed())
				PED::SET_PED_RAGDOLL_ON_COLLISION(ped.GetHandle(), false);
		}

		void onTick() override
		{
			auto ped = Stand::Self::GetPed();
			if (!ped)
				return;

			const auto handle = ped.GetHandle();
			if (PED::IS_PED_RAGDOLL(handle))
				m_ReenableAt = std::chrono::steady_clock::now() + std::chrono::seconds(2);
			else if (std::chrono::steady_clock::now() >= m_ReenableAt)
				PED::SET_PED_RAGDOLL_ON_COLLISION(handle, true);
		}

		~CommandClumsiness() override
		{
			CommandTickDispatch::RemoveCommand(this);
		}

	private:
		CommandGrace* m_Grace;
		std::chrono::steady_clock::time_point m_ReenableAt{};
	};
}

namespace Stand::Features
{
	Stand::CommandClumsiness& GetCommandClumsiness();
}
