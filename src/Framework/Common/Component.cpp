#include <iostream>
#include "Component.hpp"
#include "GameObject.hpp"
using namespace ZH;

String2Class Component::s_mapString2Class;

void Component::registerComponent(const char* name, ComponentInfo* info)
{
    String2Class::iterator iter = s_mapString2Class.find(name);
    if (iter != s_mapString2Class.end()) {
        s_mapString2Class.insert(std::pair<std::string, ComponentInfo*>(name, info));
    } else {
        iter->second = info;
    }
}

Component* Component::createComponent(const char* name)
{
    String2Class::iterator iter = s_mapString2Class.find(name);
    if (iter != s_mapString2Class.end()) {
        return iter->second->createObject();
    }
    std::cout << "class \'" << name << "\' create function no exist." << std::endl;
    return nullptr;
}

void Component::setGameObject(GameObject* object)
{
    m_pObject = object;
}

GameObject* Component::getGameObject()
{
    return m_pObject;
}

void Component::update(float delay)
{

}

const char* Component::getClassName()
{
    return "Component";
}