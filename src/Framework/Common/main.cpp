#include <cstdio>
#include "Platform.h"
#include "IApplication.hpp"
using namespace ZH;

namespace ZH
{
    extern IApplication* g_pApp;
}

int main()
{
    int ret = 0;
    
    if ((ret = g_pApp->Initialize()) != 0)
    {
        return ret;
    }

    while(!g_pApp->IsQuit()) 
    {
        g_pApp->Tick();
    }

    g_pApp->Finalize();

    return 0;
}