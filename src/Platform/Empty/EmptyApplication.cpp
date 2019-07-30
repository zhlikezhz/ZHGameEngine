#include "BaseApplication.hpp"

namespace ZH 
{
	GfxConfiguration config;
	IApplication*    g_pApp             = static_cast<IApplication*>(new BaseApplication(config));
}