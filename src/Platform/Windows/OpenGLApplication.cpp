#include <cstdio>
#include "Core/GraphicEngine.hpp"
#include "OpenGLApplication.hpp"
using namespace UpPower;

namespace UpPower
{
    GraphicConfig 		g_Config(960, 540, "Graphic Engine (Windows)(OpenGL)");
    OpenGLApplication  	g_App(g_Config);
    BaseApplication*   	g_pApp = &g_App;
}

//https://www.glfw.org/docs/latest/quick_guide.html#quick_include
int OpenGLApplication::DoInit()
{
    //初始化 glfw
    if (!glfwInit())
    {
        return -1;
    }

    //设置错误函数
    glfwSetErrorCallback(&OpenGLApplication::OnErrorHandler);

    //设置OpenGL版本3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
	//glfw创建窗口  
	m_pWindow = glfwCreateWindow(m_iConfig.m_iScreenWidth, m_iConfig.m_iScreenHeight, m_iConfig.m_pAppName, NULL, NULL);
	if (m_pWindow == NULL)
	{
		return -1;
	}

	//设置m_pWindow为OpenGL当前上下文
	glfwMakeContextCurrent(m_pWindow);
 
	//设置回调，当窗口大小调整后将调用该回调函数
	glfwSetFramebufferSizeCallback(m_pWindow, &OpenGLApplication::OnResizeWindow);
 
	// glad初始化
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return -1;
	}

	GraphicEngine::GetInstance()->DoInit();
 
    return 0;
}

void OpenGLApplication::DoFinalize()
{
	GraphicEngine::GetInstance()->DoDestroy();
    //关闭窗口
    glfwDestroyWindow(m_pWindow);
	//终止渲染 关闭并清理glfw本地资源
	glfwTerminate();
}

void OpenGLApplication::DoTick()
{
	// 使用循环达到循环渲染效果
	if (glfwWindowShouldClose(m_pWindow) == 0)
	{
        //自定义输入事件  
        OnProcessInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		OnDraw();

        //交互缓冲区，否则显示空白  
        glfwSwapBuffers(m_pWindow);
        //输入输出事件,否则无法对窗口进行交互  
        glfwPollEvents();
	}  
	else
	{
		m_bQuit = true;
	}
}

void OpenGLApplication::OnResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLApplication::OnErrorHandler(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void OpenGLApplication::OnProcessInput()
{
	if (glfwGetKey(m_pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//将窗口设置为关闭，跳出循环  
		glfwSetWindowShouldClose(m_pWindow, true);
		m_bQuit = true;
	}
}

void OpenGLApplication::OnDraw()
{
	GraphicEngine::GetInstance()->DoUpdate();
}