#include "glm/gtc/matrix_transform.hpp"
#include "MacGLApplication.hpp"
#include "GL/GLRender.hpp"
#include "GL/GLShader.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include <iostream>
using namespace ZH;

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

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
    int len = sizeof(vertices) / 4;
    std::cout << len << std::endl;
    for (int i = 0; i < len; i = i + 5) {
        mesh->addPoint(vertices[i], vertices[i+1], vertices[i+2]);
        mesh->addUV(vertices[i+3], vertices[i+4]);
    }

    ShaderParameterValue value;
    Material* material = new Material();
    value.texture = Texture::createFromFile("/Users/zouhao/Code/github/res/image/wall.jpg");
    material->addValue("ourTexture", ShaderParameterType::TEXTURE, value);

    Camera* camera = new Camera();
    camera->setZ(3.0f);

    // glm::mat4 model         = glm::mat4(1.0f); 
    // glm::mat4 view          = glm::mat4(1.0f);
    // glm::mat4 projection    = glm::mat4(1.0f);
    // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    // ShaderParameterValue value1;
    // value1.mat4x4 = projection;
    // material->addValue("projection", ShaderParameterType::MATRIX4, value1);
    // ShaderParameterValue value2;
    // value2.mat4x4 = model;
    // material->addValue("model", ShaderParameterType::MATRIX4, value2);
    // ShaderParameterValue value3;
    // value3.mat4x4 = view;
    // material->addValue("view", ShaderParameterType::MATRIX4, value3);

    GLShader* shader = GLShader::createFromFile("/Users/zouhao/Code/github/res/shader/mvp_vertex.gl", "/Users/zouhao/Code/github/res/shader/mvp_fragment.gl");
    render.setShader(shader);
    render.setMesh(mesh);
    render.setMaterial(material);
    render.setCamera(camera);

    m_renderManager.addRender(&render);

    return ret;
}

void MacGLApplication::OnDraw()
{
    m_renderManager.render();
}