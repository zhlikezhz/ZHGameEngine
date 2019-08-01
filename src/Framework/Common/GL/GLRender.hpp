#pragma once
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Render.hpp"

namespace ZH
{
    class GLRender : public Render
    {
        public:
            GLRender();
            ~GLRender();

            virtual void render();
            virtual void setMesh(Mesh* mesh);
            virtual void setShader(Shader* shader);
            virtual void setMaterial(Material* material);
    };
}