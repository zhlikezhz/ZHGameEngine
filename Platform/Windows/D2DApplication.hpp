#pragma once
#include "BaseApplication.hpp"
#include <windowsx.h>
#include <tchar.h>
#include <d2d1.h>

namespace ZH
{
    class D2DApplication : public BaseApplication
    {
    public:
        D2DApplication(GfxConfiguration& config)
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