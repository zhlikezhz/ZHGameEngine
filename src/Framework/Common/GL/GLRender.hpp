#pragma once
#include <map>
#include <string>
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Render.hpp"
#include "Camera.hpp"

namespace ZH
{
    typedef std::map<std::string, unsigned int> ShaderParameter2ID; 
    class GLRender : public Render
    {

        public:
            GLRender();
            ~GLRender();

            virtual void render();
            virtual void setMesh(Mesh* mesh);
            virtual void setShader(Shader* shader);
            virtual void setMaterial(Material* material);
            virtual void preproccessing();

            inline void setCamera(Camera* camera) {m_pCamera = camera;}
        
        private:
            Camera* m_pCamera;
            unsigned int m_uiVAO;
            unsigned int m_uiUVVBO;
            unsigned int m_uiPointVBO;
            ShaderParameter2ID m_mTextureIDs;
    };
}