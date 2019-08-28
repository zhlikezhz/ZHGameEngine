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
#include <chrono>
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
    uint32_t g_FrameNum = 3;
    size_t g_FrameTime = 1000 / g_FrameNum;
    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> microClock_type;  

    void createObject(glm::vec3 pos)
    {
        GameObject* gameObject = new GameObject();
        Transform* transform = gameObject->addComponent<Transform>();
        transform->setRotateX(-55.0f);
        transform->setPosition(pos);

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
    }
}

int MacGLApplication::Initialize()
{
    int ret = GLApplication::Initialize();

    SceneManager::getInstance()->init();

    microClock_type tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());  
    m_preFrameTime = tp.time_since_epoch().count() - g_FrameTime;

    // createObject(glm::vec3(1.0f, 1.0f, 0.0f));
    // createObject(glm::vec3(0.0f, 0.0f, 0.0f));

    Model *model = new Model("/Users/zouhao/Code/github/res/nanosuit/nanosuit.obj");

    //获取当前时间点，windows system_clock是100纳秒级别的(不同系统不一样，自己按照介绍的方法测试)，所以要转换   

    return ret;
}


void MacGLApplication::OnDraw()
{
    // microClock_type tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());  
    // size_t curTime = tp.time_since_epoch().count();
    // if (curTime - g_FrameTime >= m_preFrameTime) {
    //     SceneManager::getInstance()->update();
    //     m_preFrameTime = curTime;
    // }
    SceneManager::getInstance()->update();
}