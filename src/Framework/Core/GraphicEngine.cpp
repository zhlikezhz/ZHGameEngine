#include "Lua/LuaState.hpp"
#include "Core/GraphicEngine.hpp"
#include "Example_Test_01.hpp"
using namespace UpPower;

void GraphicEngine::DoInit()
{
	LuaState::GetInstance()->DoInit();
	m_pExample = (Example*)(new Example_Test_01());
	m_pExample->DoInit();
}

void GraphicEngine::DoUpdate()
{
	LuaState::GetInstance()->DoUpdate();
	m_pExample->DoUpdate();
}

void GraphicEngine::DoDestroy()
{
	LuaState::GetInstance()->DoDestroy();
	m_pExample->DoDestory();
}