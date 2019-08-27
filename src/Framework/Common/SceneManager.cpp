#include "Scene.hpp"
#include "SceneManager.hpp"
#include <string>
using namespace ZH;

SceneManager::SceneManager()
:m_vSceneList(),
m_pMainScene(NULL)
{
    
}

SceneManager::~SceneManager()
{
    destroy();
}

void SceneManager::init()
{
    Scene* scene = new Scene();
    m_vSceneList.push_back(scene);
    scene->setName("mainScene");
    changeScene(scene);
    scene->init();
}

void SceneManager::destroy()
{

}

void SceneManager::update()
{
    m_pMainScene->update();
}

Scene* SceneManager::getScene(std::string name)
{
    SceneList::iterator iter = m_vSceneList.begin();
    for (; iter != m_vSceneList.end(); iter++) {
        if ((*iter)->getName() == name) {
            return (*iter);
        }
    }
    return NULL;
}

Scene* SceneManager::createScene(std::string name)
{
    Scene* scene = new Scene();
    m_vSceneList.push_back(scene);
    scene->setName(name);
    scene->init();
    return scene;
}

void SceneManager::deleteScene(Scene* scene)
{
    SceneList::iterator iter = m_vSceneList.begin();
    for (; iter != m_vSceneList.end(); iter++) {
        if ((*iter) == scene) {
            m_vSceneList.erase(iter);
            break;
        }
    }
    scene->destroy();
}

Scene* SceneManager::getMainScene()
{
    return m_pMainScene;
}

void SceneManager::changeScene(Scene* scene)
{
    if (m_pMainScene != scene) {
        if (m_pMainScene != NULL) {
            m_pMainScene->stop();
        }
        m_pMainScene = scene;
        m_pMainScene->start();
    }
}
