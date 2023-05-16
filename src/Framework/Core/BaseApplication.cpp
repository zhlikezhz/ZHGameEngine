#include "Core/BaseApplication.hpp"

using namespace UpPower;

bool BaseApplication::m_bQuit = false;

BaseApplication::BaseApplication(GraphicConfig& cfg)
    :m_iConfig(cfg)
{

}

int BaseApplication::DoInit()
{
    return 0;
}

void BaseApplication::DoFinalize()
{

}

void BaseApplication::DoTick()
{

}

bool BaseApplication::IsQuit()
{
	return m_bQuit;
}