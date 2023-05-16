#pragma once
#include "Core/IManager.hpp"

extern "C"
{
#include "lua/lauxlib.h"
#include "lua/lualib.h"
#include "lua/lua.h"
}

namespace UpPower
{
	class LuaState : public IManager<LuaState>
	{
	public:
		virtual void DoInit();
		virtual void DoUpdate();
		virtual void DoDestroy();

	public:
		

	protected:
		lua_State*	m_pLuaState = nullptr; 
	};
}