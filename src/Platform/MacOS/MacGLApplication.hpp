#pragma once
#include <ctime>
#include "GL/GLApplication.hpp"

namespace ZH
{
    class MacGLApplication : public GLApplication
    {
        public:
            MacGLApplication(GfxConfiguration &config)
                : GLApplication(config) {}
            
            virtual int Initialize();

        protected:
            virtual void OnDraw();

        private:
            size_t m_preFrameTime;

    };
}