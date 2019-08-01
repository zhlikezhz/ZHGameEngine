#pragma once
#include "GL/GLApplication.hpp"
#include "RenderManager.hpp"

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
            RenderManager m_renderManager;
    };
}