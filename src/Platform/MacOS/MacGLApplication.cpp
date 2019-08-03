#include "MacGLApplication.hpp"
#include "GL/GLRender.hpp"
#include "GL/GLShader.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Texture.hpp"
using namespace ZH;

namespace ZH
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 500, 500, "Game Engine (MacOS OpenGL)");
    MacGLApplication g_App(config);
    IApplication* g_pApp = &g_App;
    GLRender render;
}

int MacGLApplication::Initialize()
{
    int ret = GLApplication::Initialize();

    Mesh* mesh = new Mesh();
    mesh->addPoint(-0.5, 0.5);
    mesh->addPoint(0.5, 0.5);
    mesh->addPoint(-0.5, -0.5);
    mesh->addPoint(0.5, -0.5);
    mesh->addPoint(0.5, 0.5);
    mesh->addPoint(-0.5, -0.5);

    mesh->addUV(0.0, 1.0);
    mesh->addUV(1.0, 1.0);
    mesh->addUV(0.0, 0.0);
    mesh->addUV(1.0, 0.0);
    mesh->addUV(1.0, 1.0);
    mesh->addUV(0.0, 0.0);

    // mesh->addPoint(-0.5f, -0.5f, 0.0f);
    // mesh->addPoint(0.5f, -0.5f, 0.0f);
    // mesh->addPoint(0.0f, 0.5f, 0.0f);
    // mesh->addUV(0.0f, 0.0f);
    // mesh->addUV(1.0f, 0.0f);
    // mesh->addUV(0.5f, 1.0f);

    Material* material = new Material();
    ShaderParameterValue value;
    value.texture = Texture::createFromFile("/Users/zouhao/Code/github/res/image/wall.jpg");
    material->addValue("ourTexture", ShaderParameterType::TEXTURE, value);

    GLShader* shader = GLShader::createFromFile("/Users/zouhao/Code/github/res/shader/uv_vertex.gl", "/Users/zouhao/Code/github/res/shader/uv_fragment.gl");

    render.setShader(shader);
    render.setMesh(mesh);
    render.setMaterial(material);

    m_renderManager.addRender(&render);

    return ret;
}

void MacGLApplication::OnDraw()
{
    m_renderManager.render();
}