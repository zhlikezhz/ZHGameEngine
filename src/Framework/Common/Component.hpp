#pragma once
#include <map>
#include <string>

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
            static void registerComponent(const char* name, ComponentInfo* info);
            static Component* createComponent(const char* name);
        
            virtual void setGameObject(GameObject* object);
            virtual GameObject* getGameObject();

            virtual const char* getClassName();

        protected:
            virtual void update(float delay);
            static String2Class s_mapString2Class;

        private:
            GameObject* m_pObject;
            friend class GameObject;
    };

    class ComponentInfo
    {
        public:
            ComponentInfo(const char* name, CreateClass func)
            {
                m_pCreateFunc = func;
                m_strClassName = name;
                Component::registerComponent(name, this);
            }

            inline Component* createObject() { return (*m_pCreateFunc)(); }
            inline std::string getClassName() { return m_strClassName;}
        
        private:
            ComponentInfo() {}

        private:
            std::string m_strClassName;
            CreateClass m_pCreateFunc;
    };

#define DECLARE_CLASS(name) \
    protected: \
        static ComponentInfo m_sComponentInfo; \
    public:  \
        static Object* createObject() {return new name;} \
        virtual const char* getClassName(); 
 
#define IMPLEMENT_CLASS_COMMON(name,func) \
    ComponentInfo name::m_sComponentInfo((#name), \
             (CreateClass) func); \
                        \
    const char* name::getClassName() \
            {return m_sComponentInfo.getClassName().c_str();}
 
#define IMPLEMENT_CLASS(name)            \
    IMPLEMENT_CLASS_COMMON(name,name::createObject) 
}