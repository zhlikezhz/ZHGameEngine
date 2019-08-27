#include "Scene.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"
#include <algorithm>
using namespace ZH;

Scene::Scene()
: m_pMainCamera(nullptr),
m_vCameraList(),
m_vGameObjectList()
{
}

Scene::~Scene()
{
    destroy();
}

void Scene::init()
{
    Camera* camera = new Camera();
    camera->setZ(3.0f);
    setMainCamera(camera);
}

void Scene::destroy()
{

}

void Scene::start()
{

}

void Scene::stop()
{

}

void Scene::update()
{
    std::vector<GameObject*>::const_iterator giter = m_vGameObjectList.cbegin();
    for (; giter != m_vGameObjectList.cend(); giter++) {
        (*giter)->update();
    }
}

void Scene::setMainCamera(Camera* camera)
{
    if (m_pMainCamera != nullptr) {
        removeCamera(m_pMainCamera);
    }
    m_pMainCamera = camera;
    addCamera(camera);
}

void Scene::addCamera(Camera* camera)
{
    std::vector<Camera*>::iterator iter = std::find(m_vCameraList.begin(), m_vCameraList.end(), camera);
    if (iter == m_vCameraList.end()) {
        m_vCameraList.push_back(camera);
    }
}

void Scene::removeCamera(Camera* camera)
{
    removeGameObject(camera);
    std::vector<Camera*>::iterator iter = std::find(m_vCameraList.begin(), m_vCameraList.end(), camera);
    if (iter != m_vCameraList.end()) {
        m_vCameraList.erase(iter);
    }
}

void Scene::removeCameraByName(const char* name)
{
    removeGameObjectByName(name);
    std::vector<Camera*>::iterator iter = m_vCameraList.begin();
    for (; iter != m_vCameraList.end(); iter++) {
        if ((*iter)->getName() == name) {
            m_vCameraList.erase(iter);
            return;
        }
    }
}

void Scene::addGameObject(GameObject* object)
{
    std::vector<GameObject*>::iterator iter = std::find(m_vGameObjectList.begin(), m_vGameObjectList.end(), object);
    if (iter == m_vGameObjectList.end()) {
        m_vGameObjectList.push_back(object);
    }
}

void Scene::removeGameObject(GameObject* object)
{
    std::vector<GameObject*>::iterator iter = std::find(m_vGameObjectList.begin(), m_vGameObjectList.end(), object);
    if (iter != m_vGameObjectList.end()) {
        m_vGameObjectList.erase(iter);
    }
}

void Scene::removeGameObjectByName(const char* name)
{
    std::vector<GameObject*>::iterator iter = m_vGameObjectList.begin();
    for (; iter != m_vGameObjectList.end(); iter++) {
        if ((*iter)->getName() == name) {
            m_vGameObjectList.erase(iter);
            return;
        }
    }
}

GameObject* Scene::getGameObjectByName(const char* name)
{
    std::vector<GameObject*>::iterator iter = m_vGameObjectList.begin();
    for (; iter != m_vGameObjectList.end(); iter++) {
        if ((*iter)->getName() == name) {
            return *iter;
        }
    }
    return nullptr;
}
