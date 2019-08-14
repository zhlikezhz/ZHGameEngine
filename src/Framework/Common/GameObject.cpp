#include "GameObject.hpp"
#include "Component.hpp"
#include "Scene.hpp"
#include <algorithm>
#include <string>
#include <iostream>
using namespace ZH;

GameObject::GameObject()
:m_strName("Object"),
m_mapName2CompList()
{
    
}

GameObject::GameObject(std::string name)
: m_strName(name),
m_mapName2CompList()
{

}

GameObject::~GameObject()
{

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

const std::vector<Component*>* GameObject::getComponents(std::string name)
{
    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter != m_mapName2CompList.end()) {
        return iter->second;
    }
    return nullptr;
}

void GameObject::update(float delay)
{
    NameToComponentList::const_iterator iter = m_mapName2CompList.cbegin();
    for (; iter != m_mapName2CompList.cend(); iter++) {
        ComponentList* compList = iter->second;
        ComponentList::const_iterator viter = compList->cbegin();
        for(; viter != compList->cend(); viter++) {
            (*viter)->update(delay);
        }
    }
}