#include "ScriptEvent.hpp"
#include "game/gta/Natives.hpp"

void SCRIPT_EVENT::Send()
{
	auto size = __SizeOfEvent;
	__SizeOfEvent = 0;
	SCRIPT::_SEND_TU_SCRIPT_EVENT_NEW(1, this, size / sizeof(std::uint32_t), PlayerBits, EventIndex);
	__SizeOfEvent = size;
}
