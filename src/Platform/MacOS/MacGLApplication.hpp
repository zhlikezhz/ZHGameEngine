#pragma once
#include "GLApplication.hpp"

namespace ZH
{
    class MacGLApplication : public GLApplication
    {
        public:
            MacGLApplication(GfxConfiguration &config)
                : GLApplication(config) { }
            
    };
}