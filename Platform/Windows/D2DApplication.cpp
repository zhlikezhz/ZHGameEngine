#include "D2DApplication.hpp"
using namespace ZH;

namespace ZH 
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, "Game");
    D2DApplication g_App(config);
    IApplication* g_pApp = &g_App;

    ID2D1Factory            *pFactory = nullptr;
    ID2D1HwndRenderTarget   *pRenderTarget = nullptr;
    ID2D1SolidColorBrush    *pCornflowerBlueBrush = nullptr;
    ID2D1SolidColorBrush    *pLightSlateGrayBrush = nullptr;
}


template<class T> void SafeRelease(T **ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != nullptr)
    {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = nullptr;
    }
}

HRESULT CreateGraphicsResources(HWND hWnd)
{
    HRESULT hr = S_OK;

    if (pRenderTarget == nullptr)
    {
        RECT rc;
        GetClientRect(hWnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(), 
            D2D1::HwndRenderTargetProperties(hWnd, size), 
            &pRenderTarget);
        
        if (SUCCEEDED(hr))
        {
            hr = pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::LightSlateGray),
                &pLightSlateGrayBrush);
        }

        if (SUCCEEDED(hr))
        {
            hr = pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
                &pCornflowerBlueBrush);
        }
    }

    return hr;
}

void DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pLightSlateGrayBrush);
    SafeRelease(&pCornflowerBlueBrush);
}

int D2DApplication::Initialize()
{
    // initialize COM
    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE))) 
        return -1;

    HINSTANCE hInstance = GetModuleHandle(nullptr);

    HWND hWnd;
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "GameEngine";

    RegisterClassEx(&wc);

    hWnd = CreateWindowExW(0,
                        L"GameEngine",      // name of the window class
                        L"1111",        // title of the window
                        WS_OVERLAPPEDWINDOW,              // window style
                        CW_USEDEFAULT,                    // x-position of the window
                        CW_USEDEFAULT,                    // y-position of the window
                        m_Config.screenWidth,             // width of the window
                        m_Config.screenHeight,            // height of the window
                        nullptr,                          // we have no parent window, NULL
                        nullptr,                          // we aren't using menus, NULL
                        hInstance,                        // application handle
                        nullptr);                         // used with multiple windows, NULL

    ShowWindow(hWnd, SW_SHOW);

    return 0;
}

void D2DApplication::Finalize()
{
    // uninitialize COM
    CoUninitialize();
}

void D2DApplication::Tick()
{
    MSG msg;
    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg); 
    }
}

LRESULT CALLBACK D2DApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_CREATE:
        {
            if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
            {
                    return -1;
            }
        }
        break;
    case WM_PAINT:
        {
            HRESULT hr = CreateGraphicsResources(hWnd);
            if (SUCCEEDED(hr))
            {
                PAINTSTRUCT ps;
                BeginPaint(hWnd, &ps);

                // start build GPU draw command
                pRenderTarget->BeginDraw();

                // clear the background with white color
                pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

                // retrieve the size of drawing area
                D2D1_SIZE_F rtSize = pRenderTarget->GetSize();

                // draw a grid background.
                int width = static_cast<int>(rtSize.width);
                int height = static_cast<int>(rtSize.height);
                for (int x = 0; x < width; x += 10)
                {
                    pRenderTarget->DrawLine(
                        D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
                        D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height), 
                        pLightSlateGrayBrush, 
                        0.5f);
                }
                for (int y = 0; y < height; y += 10)
                {
                    pRenderTarget->DrawLine(
                        D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
                        D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)), 
                        pLightSlateGrayBrush, 
                        0.5f);
                }

                // draw two rectangles
                D2D1_RECT_F rectangle1 = D2D1::RectF(
                    rtSize.width / 2 - 50.0f,
                    rtSize.height / 2 - 50.0f,
                    rtSize.width / 2 + 50.0f,
                    rtSize.height / 2 + 50.0f);

                D2D1_RECT_F rectangle2 = D2D1::RectF(
                    rtSize.width / 2 - 100.0f,
                    rtSize.height / 2 - 100.0f,
                    rtSize.width / 2 + 100.0f,
                    rtSize.height / 2 + 100.0f);

                // draw a filled rectangle
                pRenderTarget->FillRectangle(&rectangle1, pLightSlateGrayBrush);

                // draw a outline only rectangle
                pRenderTarget->DrawRectangle(&rectangle2, pCornflowerBlueBrush);

                // end GPU draw command building
                hr = pRenderTarget->EndDraw();
                if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
                {
                    DiscardGraphicsResources();
                }

                EndPaint(hWnd, &ps);
            }
        }    
        break;
    case WM_SIZE:
        if (pRenderTarget != nullptr)
        {
                RECT rc;
                GetClientRect(hWnd, &rc);
                D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);
                pRenderTarget->Resize(size);
        }
        break;
    case WM_DESTROY:
        {
            DiscardGraphicsResources();
            SafeRelease(&pFactory);
            PostQuitMessage(0);
            BaseApplication::m_bQuit = true;
            return 0;
        }
        break;
    case WM_DISPLAYCHANGE:
        {
            InvalidateRect(hWnd, nullptr, false);
        }
        break;
    }
    return DefWindowProc (hWnd, message, wParam, lParam);
}