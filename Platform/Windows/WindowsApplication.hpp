#pragma once
#include "BaseApplication.hpp"
#define WIN32_LEAN_AND_MEAN             
#include <windows.h>

namespace ZH
{
    class WindowsApplication : public BaseApplication
    {
    public:
        WindowsApplication(GfxConfiguration& config)
            : BaseApplication(config) {};

       	virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();

        static LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);
    };
}