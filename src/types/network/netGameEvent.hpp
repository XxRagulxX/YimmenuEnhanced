#pragma once

namespace rage
{
	class datBitBuffer;
	class netPlayer;

	class netGameEvent
	{
	public:
		enum class Type : uint16_t
		{
			OBJECT_ID_FREED_EVENT,
			OBJECT_ID_REQUEST_EVENT,
			ARRAY_DATA_VERIFY_EVENT,
			SCRIPT_ARRAY_DATA_VERIFY_EVENT,
			REQUEST_CONTROL_EVENT,
			GIVE_CONTROL_EVENT,
			WEAPON_DAMAGE_EVENT,
			REQUEST_PICKUP_EVENT,
			REQUEST_MAP_PICKUP_EVENT,
			GAME_CLOCK_EVENT,
			GAME_WEATHER_EVENT,
			RESPAWN_PLAYER_PED_EVENT,
			GIVE_WEAPON_EVENT,
			REMOVE_WEAPON_EVENT,
			REMOVE_ALL_WEAPONS_EVENT,
			VEHICLE_COMPONENT_CONTROL_EVENT,
			FIRE_EVENT,
			EXPLOSION_EVENT,
			START_PROJECTILE_EVENT,
			UPDATE_PROJECTILE_TARGET_EVENT,
			REMOVE_PROJECTILE_ENTITY_EVENT,
			BREAK_PROJECTILE_TARGET_LOCK_EVENT,
			ALTER_WANTED_LEVEL_EVENT,
			CHANGE_RADIO_STATION_EVENT,
			RAGDOLL_REQUEST_EVENT,
			PLAYER_TAUNT_EVENT,
			PLAYER_CARD_STAT_EVENT,
			DOOR_BREAK_EVENT,
			SCRIPTED_GAME_EVENT,
			REMOTE_SCRIPT_INFO_EVENT,
			REMOTE_SCRIPT_LEAVE_EVENT,
			MARK_AS_NO_LONGER_NEEDED_EVENT,
			CONVERT_TO_SCRIPT_ENTITY_EVENT,
			SCRIPT_WORLD_STATE_EVENT,
			CLEAR_AREA_EVENT,
			CLEAR_RECTANGLE_AREA_EVENT,
			NETWORK_REQUEST_SYNCED_SCENE_EVENT,
			NETWORK_START_SYNCED_SCENE_EVENT,
			NETWORK_STOP_SYNCED_SCENE_EVENT,
			NETWORK_UPDATE_SYNCED_SCENE_EVENT,
			INCIDENT_ENTITY_EVENT,
			GIVE_PED_SCRIPTED_TASK_EVENT,
			GIVE_PED_SEQUENCE_TASK_EVENT,
			NETWORK_CLEAR_PED_TASKS_EVENT,
			NETWORK_START_PED_ARREST_EVENT,
			NETWORK_START_PED_UNCUFF_EVENT,
			NETWORK_SOUND_CAR_HORN_EVENT,
			NETWORK_ENTITY_AREA_STATUS_EVENT,
			NETWORK_GARAGE_OCCUPIED_STATUS_EVENT,
			PED_CONVERSATION_LINE_EVENT,
			SCRIPT_ENTITY_STATE_CHANGE_EVENT,
			NETWORK_PLAY_SOUND_EVENT,
			NETWORK_STOP_SOUND_EVENT,
			NETWORK_PLAY_AIRDEFENSE_FIRE_EVENT,
			NETWORK_BANK_REQUEST_EVENT,
			NETWORK_AUDIO_BARK_EVENT,
			REQUEST_DOOR_EVENT,
			NETWORK_TRAIN_REPORT_EVENT,
			NETWORK_TRAIN_REQUEST_EVENT,
			NETWORK_INCREMENT_STAT_EVENT,
			MODIFY_VEHICLE_LOCK_WORD_STATE_DATA,
			MODIFY_PTFX_WORD_STATE_DATA_SCRIPTED_EVOLVE_EVENT,
			REQUEST_PHONE_EXPLOSION_EVENT,
			REQUEST_DETACHMENT_EVENT,
			KICK_VOTES_EVENT,
			GIVE_PICKUP_REWARDS_EVENT,
			BLOW_UP_VEHICLE_EVENT,
			NETWORK_SPECIAL_FIRE_EQUIPPED_WEAPON,
			NETWORK_RESPONDED_TO_THREAT_EVENT,
			NETWORK_SHOUT_TARGET_POSITION,
			VOICE_DRIVEN_MOUTH_MOVEMENT_FINISHED_EVENT,
			PICKUP_DESTROYED_EVENT,
			UPDATE_PLAYER_SCARS_EVENT,
			NETWORK_CHECK_EXE_SIZE_EVENT,
			NETWORK_PTFX_EVENT,
			NETWORK_PED_SEEN_DEAD_PED_EVENT,
			REMOVE_STICKY_BOMB_EVENT,
			NETWORK_CHECK_CODE_CRCS_EVENT,
			INFORM_SILENCED_GUNSHOT_EVENT,
			PED_PLAY_PAIN_EVENT,
			CACHE_PLAYER_HEAD_BLEND_DATA_EVENT,
			REMOVE_PED_FROM_PEDGROUP_EVENT,
			REPORT_MYSELF_EVENT,
			REPORT_CASH_SPAWN_EVENT,
			ACTIVATE_VEHICLE_SPECIAL_ABILITY_EVENT,
			BLOCK_WEAPON_SELECTION,
			NETWORK_CHECK_CATALOG_CRC
		};

		virtual ~netGameEvent() = default;

		virtual const char* GetName() = 0;
		virtual bool IsInScope(netPlayer* player) = 0;
		virtual bool TimeToResend(uint32_t time) = 0;
		virtual bool CanChangeScope() = 0;
		virtual void PrepareData(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};
		virtual void HandleData(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};
		virtual bool Decide(netPlayer* source_player, netPlayer* target_player) = 0;
		virtual void PrepareReply(datBitBuffer* buffer, netPlayer* reply_player) {};
		virtual void HandleReply(datBitBuffer* buffer, netPlayer* souce_player) {};
		virtual void PrepareExtraData(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};
		virtual void HandleExtraData(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};

	private:
		virtual void unk_0x60() {};
		virtual void unk_0x68() {};
		virtual void unk_0x70() {};
		virtual void unk_0x78() {};

	public:
		virtual bool operator==(netGameEvent const& other) = 0;
		virtual bool operator!=(netGameEvent const& other) = 0;

		virtual bool MustPersist() = 0;
		virtual bool MustPersistWhenOutOfScope() = 0;
		virtual bool HasTimedOut() = 0;

	public:
		Type m_Type; // 0x08
		bool m_RequiresReply; // 0x0A
	private:
		char m_padding1[0x05]; // 0x0B
	public:
		netPlayer* m_SourcePlayer; // 0x10
		netPlayer* m_TargetPlayer; // 0x18
		uint32_t m_ResendTime;     // 0x20
	private:
		uint16_t m_0x24; // 0x24
		uint8_t m_0x26;  // 0x26
		uint8_t m_0x27;  // 0x27
		uint32_t m_0x28; // 0x28
	};
	static_assert(sizeof(rage::netGameEvent) == 0x30);
}