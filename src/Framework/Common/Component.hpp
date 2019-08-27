#pragma once
#include <map>
#include <string>
#include <iostream>

#define DECLARE_CLASS(name) \
    private: \
        static ComponentInfo* m_sComponentInfo; \
    public:  \
        virtual std::string getClassName(); \
    private:\
        static Component* createObject() {return new name;} 
 
#define IMPLEMENT_CLASS_COMMON(name,func) \
    ComponentInfo* name::m_sComponentInfo = ComponentInfo::createInfo((#name), \
             (CreateClass) func); \
                        \
    std::string name::getClassName() \
            {return m_sComponentInfo->getClassName();}
 
#define IMPLEMENT_CLASS(name)            \
    IMPLEMENT_CLASS_COMMON(name,name::createObject) 

namespace ZH
{
    class GameObject;
    class Component;
    class ComponentInfo;
    typedef Component* (*CreateClass)();
    typedef std::map<std::string, ComponentInfo*> String2Class;

    class Component
    {
        public:
            static void registerComponent(std::string name, ComponentInfo* info);
            static Component* createComponent(std::string name);
        
            void setGameObject(GameObject* object);
            GameObject* getGameObject();
            virtual std::string getClassName();

        protected:
            friend class GameObject;

            virtual void update(float);
            virtual void parentChanged();

        protected:
            GameObject* m_pObject;
        
        private:
            static String2Class* s_mapString2Class;
    };

    class ComponentInfo
    {
        public:
            ComponentInfo(std::string name, CreateClass func)
            {
                m_pCreateFunc = func;
                m_strClassName = std::string(name);
                Component::registerComponent(name, this);
            }

            inline Component* createObject() { return (*m_pCreateFunc)(); }
            inline std::string getClassName() { 
                return m_strClassName;
            }

            inline static ComponentInfo* createInfo(std::string name, CreateClass func)
            {
                return (new ComponentInfo(name, func));
            }

        private:
            ComponentInfo() {}

        private:
            std::string m_strClassName;
            CreateClass m_pCreateFunc;
    };


}