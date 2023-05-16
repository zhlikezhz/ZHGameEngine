#include "Core/Platform.h"
#include "Core/BaseApplication.hpp"
using namespace UpPower;

namespace UpPower
{
    extern BaseApplication* g_pApp;
}

int main()
{
    int ret = 0;
    
    if ((ret = g_pApp->DoInit()) != 0)
    {
        return ret;
    }

    while(!g_pApp->IsQuit()) 
    {
        g_pApp->DoTick();
    }

    g_pApp->DoFinalize();

    return 0;
}