#include "ControllerInputs.hpp"
#include "FloatCommand.hpp"
#include "LoopedCommand.hpp"
#include "Natives.hpp"
#include "Self.hpp"

#include <algorithm>

// Ported from stand-reference's src/Commands/Self/CommandLevitate.cpp -
// the actual free-flight movement (freeze position, read camera yaw,
// move relative to it, commit the new position every tick) and its
// acceleration ramp, using this project's own Entity/Self/native API
// instead of Stand's own AbstractEntity/free_movement()/Input
// abstractions. Real Stand's version also has a ground/water-height
// "hover assist" (raycasting to snap/nudge Z toward the surface below)
// and a passive up/down bobbing effect on top of this - both left out
// deliberately rather than guessed at: they depend on Stand's own
// shapetest/water-level natives and heightmap lookup, which this
// project has no verified equivalent of yet. This is a real, complete
// free-flight feature without them, not a stand-in for the full one.
namespace YimMenu::Features
{
	static FloatCommand _LevitateSpeed{"levitatespeed", "Move Speed", "How fast you move while levitating", 0.01f, 10000.0f, 1.0f};
	static FloatCommand _LevitateSprintSpeed{"levitatesprintmultiplier", "Sprint Speed", "How fast you move while levitating and holding Sprint", 0.01f, 10000.0f, 5.0f};
	static FloatCommand _LevitateAccel{"levitateaccel", "Acceleration", "Ramps move speed up the longer you hold a direction (0 to disable)", 0.0f, 10.0f, 0.0f};

	class Levitate : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		float m_CurrentSpeed = 0.0f;

		virtual void OnEnable() override
		{
			m_CurrentSpeed = _LevitateSpeed.GetState();
		}

		virtual void OnDisable() override
		{
			if (auto ped = Self::GetPed())
				ped.SetFrozen(false);
		}

		virtual void OnTick() override
		{
			static constexpr ControllerInputs controls[] = {ControllerInputs::INPUT_SPRINT, ControllerInputs::INPUT_JUMP, ControllerInputs::INPUT_DUCK, ControllerInputs::INPUT_MOVE_UP_ONLY, ControllerInputs::INPUT_MOVE_DOWN_ONLY, ControllerInputs::INPUT_MOVE_LEFT_ONLY, ControllerInputs::INPUT_MOVE_RIGHT_ONLY};
			for (const auto& control : controls)
				PAD::DISABLE_CONTROL_ACTION(0, static_cast<int>(control), true);

			auto ped = Self::GetPed();
			if (!ped || !ped.IsValid())
				return;

			rage::fvector3 dir{};
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
				dir.y += 1.0f;
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
				dir.y -= 1.0f;
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
				dir.x -= 1.0f;
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
				dir.x += 1.0f;
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_JUMP))
				dir.z += 1.0f;
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_DUCK))
				dir.z -= 1.0f;

			const bool sprinting = PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT);
			const bool moving = (dir.x != 0.0f || dir.y != 0.0f || dir.z != 0.0f);

			if (moving && !sprinting && _LevitateAccel.GetState() != 0.0f)
				m_CurrentSpeed = std::min(m_CurrentSpeed + _LevitateAccel.GetState() / 100.0f, 12.5f);
			else
				m_CurrentSpeed = sprinting ? _LevitateSprintSpeed.GetState() : _LevitateSpeed.GetState();

			ped.SetFrozen(true);

			if (!moving)
				return;

			const auto rot = CAMERA::GET_GAMEPLAY_CAM_ROT(2);
			ped.SetRotation({0.0f, 0.0f, rot.z});

			const auto offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped.GetHandle(), dir.x * m_CurrentSpeed, dir.y * m_CurrentSpeed, dir.z * m_CurrentSpeed);
			ped.SetPosition({offset.x, offset.y, offset.z});
		}
	};

	static Levitate _Levitate{"levitate", "Levitation", "Fly freely, hovering in place when still - WASD to move, Jump/Duck for up/down, hold Sprint to go faster"};
}
