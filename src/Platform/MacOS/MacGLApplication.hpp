#pragma once
#include "OpenGLApplication.hpp"

namespace ZH
{
    class MacGLApplication : public OpenGLApplication
    {
        public:
            MacGLApplication(GfxConfiguration &config)
                : OpenGLApplication(config) { }
            
    };
}