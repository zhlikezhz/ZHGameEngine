#include "glm/gtc/matrix_transform.hpp"
#include "MacGLApplication.hpp"
#include "SceneManager.hpp"
#include "GL/GLRender.hpp"
#include "GL/GLShader.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Model.hpp"
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
}

int MacGLApplication::Initialize()
{
    int ret = GLApplication::Initialize();
    SceneManager::getInstance()->init();

    GameObject* gameObject = new GameObject();
    Transform* transform = gameObject->addComponent<Transform>();
    transform->setRotateX(-55.0f);

    Material* material = gameObject->addComponent<Material>();
    GLShader* shader = GLShader::createFromFile("/Users/zouhao/Code/github/res/shader/mvp_vertex.gl", "/Users/zouhao/Code/github/res/shader/mvp_fragment.gl");
    material->setShader(shader);

    ShaderParameterValue value;
    value.texture = Texture::createFromFile("/Users/zouhao/Code/github/res/image/wall.jpg");
    material->addValue("ourTexture", ShaderParameterType::TEXTURE, value);

    Mesh* mesh = gameObject->addComponent<Mesh>();
    int len = sizeof(vertices) / 4;
    for (int i = 0; i < len; i = i + 5) {
        mesh->addPoint(glm::vec3(vertices[i], vertices[i+1], vertices[i+2]));
        mesh->addUV(glm::vec2(vertices[i+3], vertices[i+4]));
    }

    gameObject->addComponent<GLRender>();


    // Model *model = new Model("/Users/zouhao/Code/github/res/nanosuit/nanosuit.obj");
    // g_scene.addGameObject(model);

    return ret;
}

void MacGLApplication::OnDraw()
{
    SceneManager::getInstance()->update();
}