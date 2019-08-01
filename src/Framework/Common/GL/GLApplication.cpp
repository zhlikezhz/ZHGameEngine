#include "GLApplication.hpp"
#include <iostream>
using namespace ZH;

namespace ZH
{
    void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}


int GLApplication::Initialize()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_pWin = glfwCreateWindow(m_Config.screenWidth, m_Config.screenHeight, m_Config.appName, NULL, NULL);
    if (m_pWin == NULL) 
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(m_pWin);
    glfwSetFramebufferSizeCallback(m_pWin, ZH::FramebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    return 0;
}

void GLApplication::Finalize()
{
    glfwTerminate();
}

void GLApplication::Tick()
{
    if (glfwWindowShouldClose(m_pWin)) {
        m_bQuit = true;
        return;
    }

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    OnDraw();

    glfwSwapBuffers(m_pWin);
    glfwPollEvents();
}