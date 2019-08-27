#include "GameObject.hpp"
#include "Component.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include <algorithm>
#include <string>
#include <iostream>
using namespace ZH;

GameObject::GameObject()
:m_strName("Object"),
m_mapName2CompList()
{
    Scene* scene = SceneManager::getInstance()->getMainScene();
    scene->addGameObject(this);
}

GameObject::GameObject(std::string name)
: m_strName(name),
m_mapName2CompList()
{
    Scene* scene = SceneManager::getInstance()->getMainScene();
    scene->addGameObject(this);
}

GameObject::~GameObject()
{
    destroy();
}

void GameObject::destroy()
{

}

void GameObject::update()
{
    NameToComponentList::const_iterator iter = m_mapName2CompList.cbegin();
    for (; iter != m_mapName2CompList.cend(); iter++) {
        ComponentList* compList = iter->second;
        ComponentList::const_iterator viter = compList->cbegin();
        for(; viter != compList->cend(); viter++) {
            (*viter)->update(1.0f);
        }
    }
}

Component* GameObject::addComponent(Component* comp)
{
    comp->setGameObject(this);
    std::string name = comp->getClassName();
    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter == m_mapName2CompList.end()) {
        ComponentList* compList = new ComponentList();
        compList->push_back(comp);
        m_mapName2CompList.insert(std::pair<std::string, ComponentList*>(name, compList));
    } else {
        ComponentList* list = m_mapName2CompList[name];
        list->push_back(comp);
    }
    return comp;
}

Component* GameObject::addComponent(std::string name)
{
    Component* comp = Component::createComponent(name);
    if (comp == nullptr) {
        return nullptr;
    }
    addComponent(comp);
    return comp;
}

void GameObject::removeComponent(Component* comp)
{
    std::string name = comp->getClassName();
    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter != m_mapName2CompList.end()) {
        ComponentList* compList = iter->second;
        ComponentList::const_iterator viter = compList->cbegin();
        for(; viter != compList->cend(); viter++) {
            if (*viter == comp) {
                compList->erase(viter);
                return;
            }
        }
    }
}

void GameObject::removeComponents(std::string name)
{
    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter != m_mapName2CompList.end()) {
        m_mapName2CompList.erase(iter);
    }
}

Component* GameObject::getComponent(std::string name)
{
    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter != m_mapName2CompList.end()) {
        ComponentList* compList = iter->second;
        if (compList->size() > 0) {
            return (*compList)[0];
        }
    }
    return nullptr;
}

std::vector<Component*> GameObject::getComponents(std::string name)
{
    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter != m_mapName2CompList.end()) {
        return (*iter->second);
    }
    ComponentList* tmp = new ComponentList();
    return *tmp;
}

void GameObject::addChild(GameObject* object)
{
    GObjectChildren::iterator iter = m_vGObjectChildren.begin();
    for (; iter != m_vGObjectChildren.end(); iter++) {
        if ((*iter) == object) {
            return;
        }
    }
    m_vGObjectChildren.push_back(object);
}

void GameObject::removeChild(GameObject* object)
{
    GObjectChildren::iterator iter = m_vGObjectChildren.begin();
    for (; iter != m_vGObjectChildren.end(); iter++) {
        if ((*iter) == object) {
            m_vGObjectChildren.erase(iter);
            return;
        }
    }
}

GameObject* GameObject::getChild(const char* name)
{
    GObjectChildren::iterator iter = m_vGObjectChildren.begin();
    for (; iter != m_vGObjectChildren.end(); iter++) {
        if ((*iter)->getName() == name) {
            return *iter;
        }
    }
    return NULL;
}

std::vector<GameObject*> GameObject::getChildren()
{
    return m_vGObjectChildren;
}

void GameObject::setParent(GameObject* obj)
{
    if (m_pGObjectParent == obj) {
        return;
    }

    if (m_pGObjectParent != NULL) {
        m_pGObjectParent->removeChild(obj);
    }
    m_pGObjectParent = obj;
    obj->addChild(this);

    NameToComponentList::iterator iter = m_mapName2CompList.begin();
    for (; iter != m_mapName2CompList.end(); iter++) {
        ComponentList cmpList = *(iter->second);
        ComponentList::iterator citer = cmpList.begin();
        for (; citer != cmpList.end(); citer++) {
            (*citer)->parentChanged();
        }
    }
}

Camera* GameObject::getCamera()
{
    return SceneManager::getInstance()->getMainScene()->getMainCamera();
}