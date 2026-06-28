#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Natives.hpp"

#include <chrono>

namespace YimMenu::Features
{
    class AutoCollectTargets : public LoopedCommand
    {
        using LoopedCommand::LoopedCommand;

    private:
        std::chrono::steady_clock::time_point m_LastClick =
            std::chrono::steady_clock::now();

    public:
        virtual void OnTick() override
        {
            using namespace std::chrono;

            // Match util.yield(50)
            if (steady_clock::now() - m_LastClick < milliseconds(50))
                return;

            m_LastClick = steady_clock::now();

            // Don't click while pause menu is open
            if (HUD::IS_PAUSE_MENU_ACTIVE())
                return;

            // Simulate left mouse click (same as Lua)
            PAD::SET_CONTROL_VALUE_NEXT_FRAME(0, 237, 1.0f);
        }

        virtual void OnDisable() override
        {
            // Nothing to clean up
        }
    };

    static AutoCollectTargets _AutoCollectTargets{
        "autocollecttargets",
        "Auto Collect Targets",
        "Automatically clicks the left mouse button."
    };
}