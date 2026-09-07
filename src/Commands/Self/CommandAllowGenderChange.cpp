#include "Commands/CommandToggle.hpp"
#include "World/Stats.hpp"

namespace StandEnhanced::Features
{
	class AllowGenderChange : public CommandToggle
	{
		using CommandToggle::CommandToggle;

		virtual void OnEnable() override
		{
			Stats::SetInt("MPX_ALLOW_GENDER_CHANGE", 52);
		}

		virtual void OnDisable() override
		{
			Stats::SetInt("MPX_ALLOW_GENDER_CHANGE", 0);
		}
	};

	static AllowGenderChange _AllowGenderChange{"allowgenderchange", "Allow Gender Change", "Allows the player to change the character's gender"};
}