#include "Render.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
using namespace ZH;

void Render::render()
{

}

void Render::setMesh(Mesh* mesh)
{
    m_pMesh = mesh;
}

void Render::setShader(Shader* shader)
{
    m_pShader = shader;
}

void Render::setMaterial(Material* material)
{
    m_pMaterial = material;
}
