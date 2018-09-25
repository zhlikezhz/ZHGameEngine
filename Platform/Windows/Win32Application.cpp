#include "Win32Application.hpp"
#include <tchar.h>
using namespace ZH;

namespace ZH 
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, "Game");
    Win32Application g_App(config);
    IApplication* g_pApp = &g_App;
}

int Win32Application::Initialize()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    HWND hWnd;
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
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
                        NULL,                             // we have no parent window, NULL
                        NULL,                             // we aren't using menus, NULL
                        hInstance,                        // application handle
                        NULL);                            // used with multiple windows, NULL

    ShowWindow(hWnd, SW_SHOW);

    return 0;
}

void Win32Application::Finalize()
{
}

void Win32Application::Tick()
{
    MSG msg;
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg); 
    }
}

LRESULT CALLBACK Win32Application::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT rec = {20, 20, 60, 80};
            HBRUSH brush = (HBRUSH) GetStockObject(BLACK_BRUSH);
            FillRect(hdc, &rec, brush);
            EndPaint(hWnd, &ps);
        } 
        break;
    case WM_DESTROY:
        {
            PostQuitMessage(0);
            BaseApplication::m_bQuit = true;
            return 0;
        }
    }
    return DefWindowProc (hWnd, message, wParam, lParam);
}