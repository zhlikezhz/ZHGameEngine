#pragma once
#include "BaseApplication.hpp"
#include <windowsx.h>
#include <tchar.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
using namespace DirectX::PackedVector;
using namespace DirectX;

namespace ZH
{
    class D3DApplication : public BaseApplication
    {
    public:
        D3DApplication(GfxConfiguration& config)
            : BaseApplication(config) {};

       	virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();

        static LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);
    
    public:
        IDXGISwapChain  *m_pSwapchain = nullptr;
        ID3D11Device    *m_pDev = nullptr;

    };
}