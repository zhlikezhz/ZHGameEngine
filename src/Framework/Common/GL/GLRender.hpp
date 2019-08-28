#pragma once
#include <map>
#include <string>
#include "Render.hpp"

namespace ZH
{
    class Camera;
    typedef std::map<std::string, unsigned int> ShaderParameter2ID; 

    class GLRender : public Render
    {
        DECLARE_CLASS(GLRender)

        public:
            GLRender();
            ~GLRender();

            virtual void render();
            virtual void preproccessing();
            virtual void update(float);
        
        private:
            Camera* m_pCamera;
            unsigned int m_uiVAO;
            unsigned int m_uiUVVBO;
            unsigned int m_uiPointVBO;
            unsigned int m_uiNormalVBO;
            unsigned int m_uiIndexEBO;
            ShaderParameter2ID m_mTextureIDs;
    };
}