#pragma once
#include "BaseApplication.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace ZH
{
    class GLApplication: public BaseApplication
    {
        public:
            GLApplication(GfxConfiguration &config)
                : BaseApplication(config) { }
            
            virtual int Initialize();
            virtual void Finalize();
            virtual void Tick();
        
        protected:
            GLFWwindow* m_pWin = NULL;
    };
}