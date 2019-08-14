#include "glm/gtc/matrix_transform.hpp"
#include "MacGLApplication.hpp"
#include "GL/GLRender.hpp"
#include "GL/GLShader.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "GameObject.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
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
    Scene g_scene;
}

int MacGLApplication::Initialize()
{
    int ret = GLApplication::Initialize();

    Camera* camera = new Camera();
    // camera->setRotateX(10.0f);
    // camera->setRotateY(10.0f);
    camera->setRotateZ(45.0f);
    camera->setZ(3.0f);
    g_scene.addCamera(camera);

    GameObject* gameObject = new GameObject();
    g_scene.addGameObject(gameObject);
    gameObject->setCamera(camera);

    Transform* transform = gameObject->addComponent<Transform>();
    transform->setRotateX(-55.0f);
    // transform->setRotateY(-55.0f);

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

    return ret;
}

void MacGLApplication::OnDraw()
{
    g_scene.update(0.1f);
}