#pragma once
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Material.hpp"

namespace ZH
{
    class Render
    {
        public:
            virtual void render();
            virtual void setMesh(Mesh* mesh);
            virtual void setShader(Shader* shader);
            virtual void setMaterial(Material* material);

        protected:
            Mesh* m_pMesh;
            Shader* m_pShader;
            Material* m_pMaterial;
    };
}