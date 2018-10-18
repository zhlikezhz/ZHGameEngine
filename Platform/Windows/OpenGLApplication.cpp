#include "OpenGLApplication.hpp"
using namespace ZH;

namespace ZH 
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, "Game Engine From Scratch (Windows)");
    OpenGLApplication  g_App(config);
    IApplication*       g_pApp = &g_App;
}

int OpenGLApplication::Initialize()
{
    int result = 0;
    if ((result = BaseApplication::Initialize()) != 0) 
    {
        return result;
    }

    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASSEXW wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEXW));

    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"GameEngine OpenGL";

    // register the window class
    RegisterClassExW(&wc);
    
    // create the window and use the result as the handle
    m_hWnd = CreateWindowExW(0,
                        L"GameEngine OpenGL",      // name of the window class
                        (LPCWSTR)m_Config.appName,             // title of the window
                        WS_OVERLAPPEDWINDOW,              // window style
                        CW_USEDEFAULT,                    // x-position of the window
                        CW_USEDEFAULT,                    // y-position of the window
                        m_Config.screenWidth,             // width of the window
                        m_Config.screenHeight,            // height of the window
                        NULL,                             // we have no parent window, NULL
                        NULL,                             // we aren't using menus, NULL
                        hInstance,                        // application handle
                        NULL);                            // used with multiple windows, NULL
    
    m_hDC = GetDC(m_hWnd);
    SetGLPixelFormat();
    CreateGLRenderingContext();
    ResizeGLScene(m_Config.screenHeight, m_Config.screenHeight);
    InitGL();

    ShowWindow(m_hWnd, SW_SHOW);

    return result;
}

void OpenGLApplication::Finalize()
{

}

void OpenGLApplication::Tick()
{
    MSG msg;
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); 
    }
}

bool DrawGLScene()
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存
    glLoadIdentity();                                   //重置当前的模型观察矩阵
    return true;
}

LRESULT CALLBACK OpenGLApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_PAINT:
        {
            DrawGLScene();
        } break;

    case WM_DESTROY:
        {
            PostQuitMessage(0);
            BaseApplication::m_bQuit = true;
            return 0;
        }
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}

bool OpenGLApplication::ResizeGLScene(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);                //重置当前视口
    glMatrixMode(GL_PROJECTION);                    //选择投影矩阵
    glLoadIdentity();                               //重置投影矩阵
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f); //设置视口的大小
    glMatrixMode(GL_MODELVIEW);                     //选择模型观察矩阵
    glLoadIdentity();                               //重置模型观察矩阵
    return true;
}

bool OpenGLApplication::CreateGLRenderingContext()
{
    m_hRC = wglCreateContext(m_hDC);
    wglMakeCurrent(m_hDC, m_hRC);
    return true;
}

bool OpenGLApplication::SetGLPixelFormat()
{
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),  //格式描述符大小
        1,                              //版本号
        PFD_DRAW_TO_WINDOW |            //格式支持窗口
        PFD_SUPPORT_OPENGL |            //格式必须支持OpenGL
        PFD_DOUBLEBUFFER,               //格式必须支持双缓冲
        PFD_TYPE_RGBA,                  //RGBA颜色格式
        32,                             //颜色的位
        0, 0, 0, 0, 0, 0,               //忽略的色彩位
        0,                              //无Alpha缓存
        0,                              //忽略Shift Bit
        0,                              //无累加缓存
        0, 0, 0, 0,                     //忽略聚集位
        16,                             //16位Z缓存（深度缓存）
        0,                              //无模板缓存
        0,                              //无辅助缓存
        PFD_MAIN_PLANE,                 //主绘图层
        0,                              //不适用重叠层
        0, 0, 0                         //忽略层遮罩
    };
    int pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
    SetPixelFormat(m_hDC, pixelFormat, &pfd);
    return true;
}

bool OpenGLApplication::InitGL()
{
    glShadeModel(GL_SMOOTH);                            //启动阴影平滑
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);               //黑色背景
    glClearDepth(1.0f);                                 //设置深度缓存
    glEnable(GL_DEPTH_TEST);                            //启动深度测试
    glDepthFunc(GL_LEQUAL);                             //所做深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //告诉系统对透视进行修正
    return true;
}