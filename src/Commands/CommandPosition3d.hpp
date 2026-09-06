#pragma once
#include "Game/vector.hpp"
#include "Commands/Command.hpp"

namespace YimMenu
{
	class CommandPosition3d : public Command
	{
	protected:
		virtual void OnChange() {};
		virtual void OnCall() override;
		virtual void SaveState(nlohmann::json& value) override;
		virtual void LoadState(nlohmann::json& value) override;

		rage::fvector3 m_State{};

	public:
		CommandPosition3d(std::string name, std::string label, std::string description, rage::fvector3 def_val = {});
		rage::fvector3 GetState();
		void SetState(const rage::fvector3& state);
	};
}