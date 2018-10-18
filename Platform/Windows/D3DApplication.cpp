#include "D3DApplication.hpp"
using namespace ZH;

namespace ZH
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, "Game D3D");
    D3DApplication g_App(config);
    IApplication* g_pApp = &g_App;
}

int D3DApplication::Initialize()
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

void D3DApplication::Finalize()
{
    // uninitialize COM
    CoUninitialize();
}

void D3DApplication::Tick()
{

}

void D3DApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}