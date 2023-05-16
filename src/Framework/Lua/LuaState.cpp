#include <cstdio>
#include "Lua/LuaState.hpp"
using namespace UpPower;

void LuaState::DoInit()
{
	m_pLuaState = luaL_newstate();
	if (m_pLuaState == nullptr)
	{
		fprintf(stderr, "connot create lua state: not enough memory.");
		return ;
	}
	puts("create lua state.");
}

void LuaState::DoUpdate()
{

}

void LuaState::DoDestroy()
{
	if (m_pLuaState != nullptr)
	{
		lua_close(m_pLuaState);
		m_pLuaState = nullptr;
	}
}