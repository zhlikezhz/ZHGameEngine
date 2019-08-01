#include "RenderManager.hpp"
#include "Render.hpp"
using namespace ZH;

RenderManager::RenderManager()
:m_vRenderQueue()
{

}

void RenderManager::render()
{
    for (std::vector<Render*>::iterator iter = m_vRenderQueue.begin(); iter != m_vRenderQueue.end(); iter++)
    {
        (*iter)->render();
    }
}