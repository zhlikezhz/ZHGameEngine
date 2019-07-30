#pragma once
#include "BaseApplication.hpp"
#include <windows.h>
#include <tchar.h>
#include <GL/glew.h>
#include <GL/glut.h>

namespace ZH
{
    class OpenGLApplication : public BaseApplication
    {
    public:
        OpenGLApplication(GfxConfiguration& config) 
            : BaseApplication(config) {};
        
        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();

        static LRESULT CALLBACK WindowProc(HWND hWnd,
                        UINT message,
                        WPARAM wParam,
                        LPARAM lParam);
    
    private:
        bool InitGL();
        bool SetGLPixelFormat();
        bool CreateGLRenderingContext();
        bool ResizeGLScene(GLsizei width, GLsizei height);

    private:
        HWND    m_hWnd;
        HDC     m_hDC;
        HGLRC   m_hRC;
    };
}