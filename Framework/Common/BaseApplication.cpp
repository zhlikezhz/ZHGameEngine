#include <iostream>
#include "BaseApplication.hpp"

using namespace ZH;

bool BaseApplication::m_bQuit = false;

BaseApplication::BaseApplication(GfxConfiguration& cfg)
    :m_Config(cfg)
{

}

int BaseApplication::Initialize()
{
    int result = 0;
    std::cout << m_Config;
	return result;
}

void BaseApplication::Finalize()
{

}

void BaseApplication::Tick()
{

}

bool BaseApplication::IsQuit()
{
	return m_bQuit;
}