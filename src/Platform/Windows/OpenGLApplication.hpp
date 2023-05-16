/**
 * @file OpenGLApplication.hpp
 * @brief 
 * @author 邹浩 (zouhaodata@gmail.com)
 * @version 1.0.0
 * @date 2021-06-18
 * 
 * @copyright Copyright (c) 2021  UpPower Studio
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version   <th>Author   <th>Description
 * <tr><td>2021-06-18 <td>1.0.0     <td>邹浩     <td>内容
 * </table>
 */
#pragma once
#define GLFW_INCLUDE_NONE
#include "Core/BaseApplication.hpp"
#include "glfw/glfw3.h"
#include "glad/glad.h"
#include <windows.h>
#include <tchar.h>

namespace UpPower
{
    class OpenGLApplication : public BaseApplication
    {
    public:
        OpenGLApplication(GraphicConfig& config) 
            : BaseApplication(config) {};
        
        virtual int DoInit();
        virtual void DoFinalize();
        virtual void DoTick();
    
    protected:
        virtual void OnDraw();

    private:
        void OnProcessInput();
        static void OnErrorHandler(int error, const char* description);
        static void OnResizeWindow(GLFWwindow* window, int width, int height);

    private:
        GLFWwindow *m_pWindow = nullptr;
    };
}