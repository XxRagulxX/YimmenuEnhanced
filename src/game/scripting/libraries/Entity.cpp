#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/Entity.hpp"

namespace YimMenu::Lua
{
	// TODO: we need to automate this
	class Entity : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int New(lua_State* state)
		{
			CreateObject<YimMenu::Entity>(state, luaL_checkinteger(state, 1));
			return 1;
		}

		static int GetHandle(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Entity>(state, 1).GetHandle());
			return 1;
		}

		static int IsValid(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsValid());
			return 1;
		}

		static int IsPed(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsPed());
			return 1;
		}

		static int IsVehicle(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsVehicle());
			return 1;
		}

		static int IsObject(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsObject());
			return 1;
		}

		static int IsPlayer(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsPlayer());
			return 1;
		}

		static int IsMissionEntity(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsMissionEntity());
			return 1;
		}

		static int GetModel(lua_State* state)
		{
			lua_pushinteger(state, (int)GetObject<YimMenu::Entity>(state, 1).GetModel());
			return 1;
		}

		static int GetPosition(lua_State* state)
		{
			CopyObject<rage::fvector3>(state, GetObject<YimMenu::Entity>(state, 1).GetPosition());
			return 1;
		}

		static int GetRotation(lua_State* state)
		{
			CopyObject<rage::fvector3>(state, GetObject<YimMenu::Entity>(state, 1).GetRotation(lua_gettop(state) >= 2 ? luaL_checkinteger(state, 2) : 2));
			return 1;
		}

		static int GetVelocity(lua_State* state)
		{
			CopyObject<rage::fvector3>(state, GetObject<YimMenu::Entity>(state, 1).GetVelocity());
			return 1;
		}

		static int SetPosition(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetPosition(GetObject<rage::fvector3>(state, 2));
			return 0;
		}

		static int SetRotation(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetRotation(GetObject<rage::fvector3>(state, 2), lua_gettop(state) >= 3 ? luaL_checkinteger(state, 3) : 2);
			return 0;
		}

		static int SetVelocity(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetVelocity(GetObject<rage::fvector3>(state, 2));
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "Entity");
			{
				lua_newtable(state);
				{
					SetFunction(state, GetHandle, "get_handle");
					SetFunction(state, IsValid, "is_valid");
					SetFunction(state, IsPed, "is_ped");
					SetFunction(state, IsVehicle, "is_vehicle");
					SetFunction(state, IsObject, "is_object");
					SetFunction(state, IsPlayer, "is_player");
					SetFunction(state, IsMissionEntity, "is_mission_entity");
					SetFunction(state, GetModel, "get_model");
					SetFunction(state, GetPosition, "get_position");
					SetFunction(state, GetRotation, "get_rotation");
					SetFunction(state, GetVelocity, "get_velocity");
					SetFunction(state, SetPosition, "set_position");
					SetFunction(state, SetRotation, "set_rotation");
					SetFunction(state, SetVelocity, "set_velocity");
				}
				lua_setfield(state, -2, "__index"); // prototype
			}
			Metatable<YimMenu::Entity>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "Entity");
		}
	};

	Entity _Entity;
}