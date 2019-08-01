#pragma once
#include <vector>
#include "Render.hpp"

namespace ZH
{
    class RenderManager
    {
        public:
            RenderManager();
            void render();

            inline void addRender(Render* render) {
                m_vRenderQueue.push_back(render);
            }

        private:
            std::vector<Render*> m_vRenderQueue;
    };
}
