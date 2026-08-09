#include "Command.hpp"
#include "Self.hpp"

namespace YimMenu::Features
{
	class Suicide : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			LOG(INFO) << "Exceptional test: triggering access violation";

			volatile int* invalid_address =
			    reinterpret_cast<volatile int*>(0x1);

			*invalid_address = 1234;
		}
	};


	static Suicide _Suicide{"suicide", "Suicide", "Triggers an exception for Exceptional testing"};
}