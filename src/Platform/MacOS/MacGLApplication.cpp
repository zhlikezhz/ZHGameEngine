#include "MacGLApplication.hpp"
using namespace ZH;

namespace ZH
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 520, "Game Engine (MacOS OpenGL)");
    MacGLApplication g_App(config);
    IApplication* g_pApp = &g_App;
}

