#include "GameObject.hpp"
#include "Component.hpp"
#include "Scene.hpp"
#include <algorithm>
using namespace ZH;

GameObject::GameObject()
:m_strName("Object"),
m_mapName2CompList()
{
    
}

GameObject::GameObject(const char* name)
: m_strName(name),
m_mapName2CompList()
{

}

GameObject::~GameObject()
{

}

Component* GameObject::addComponent(Component* comp)
{
    const char* name = comp->getClassName();
    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter == m_mapName2CompList.end()) {
        ComponentList compList;
        compList.push_back(comp);
        m_mapName2CompList.insert(std::pair<std::string, ComponentList>(name, compList));
    }
    return comp;
}

Component* GameObject::addComponent(const char* name)
{
    Component* comp = Component::createComponent(name);
    if (comp == nullptr) {
        return nullptr;
    }

    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter == m_mapName2CompList.end()) {
        ComponentList compList;
        compList.push_back(comp);
        m_mapName2CompList.insert(std::pair<std::string, ComponentList>(name, compList));
    }
    return comp;
}

void GameObject::removeComponent(Component* comp)
{
    const char* name = comp->getClassName();
    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter != m_mapName2CompList.end()) {
        ComponentList compList = iter->second;
        ComponentList::const_iterator viter = compList.cbegin();
        for(; viter != compList.cend(); viter++) {
            if (*viter == comp) {
                compList.erase(viter);
                return;
            }
        }
    }
}


void GameObject::removeComponents(const char* name)
{
    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter != m_mapName2CompList.end()) {
        m_mapName2CompList.erase(iter);
    }
}

Component* GameObject::getComponent(const char* name)
{
    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter != m_mapName2CompList.end()) {
        ComponentList compList = iter->second;
        if (compList.size() > 0) {
            return compList[0];
        }
    }
    return nullptr;
}

const std::vector<Component*>* GameObject::getComponents(const char* name)
{
    NameToComponentList::iterator iter = m_mapName2CompList.find(name);
    if (iter != m_mapName2CompList.end()) {
        return &(iter->second);
    }
    return nullptr;
}

void GameObject::update(float delay)
{
    NameToComponentList::const_iterator iter = m_mapName2CompList.cbegin();
    for (; iter != m_mapName2CompList.cend(); iter++) {
        ComponentList compList = iter->second;
        ComponentList::const_iterator viter = compList.cbegin();
        for(; viter != compList.cend(); viter++) {
            (*viter)->update(delay);
        }
    }
}