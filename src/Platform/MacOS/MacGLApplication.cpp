#include "MacGLApplication.hpp"
#include "GL/GLRender.hpp"
#include "GL/GLShader.hpp"
#include "Mesh.hpp"
using namespace ZH;

namespace ZH
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 520, "Game Engine (MacOS OpenGL)");
    MacGLApplication g_App(config);
    IApplication* g_pApp = &g_App;
    GLRender render;
}

int MacGLApplication::Initialize()
{
    int ret = GLApplication::Initialize();

    Mesh* mesh = new Mesh();
    mesh->addTriangle(-0.5f, -0.5f, 0.0f);
    mesh->addTriangle(0.5f, -0.5f, 0.0f);
    mesh->addTriangle(0.0f, 0.5f, 0.0f);
    render.setMesh(mesh);

    GLShader* shader = GLShader::createFromFile("/Users/zouhao/Code/github/res/vertex.gl", "/Users/zouhao/Code/github/res/fragment.gl");
    render.setShader(shader);

    m_renderManager.addRender(&render);

    return ret;
}

void MacGLApplication::OnDraw()
{
    m_renderManager.render();
}