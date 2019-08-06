#pragma once
#include <map>
#include <vector>
#include <string>

namespace ZH
{
    class Scene;
    class Component;
    class GameObject
    {
        typedef std::vector<Component*> ComponentList;
        typedef std::map<std::string, ComponentList> NameToComponentList;
        public:
            GameObject();
            ~GameObject();
            GameObject(const char* name);

            Component* addComponent(Component* comp);
            Component* addComponent(const char* name);

            void removeComponent(Component* comp);
            void removeComponents(const char* name);

            Component* getComponent(const char* name);
            const std::vector<Component*>* getComponents(const char* name);

            inline std::string getName() { return m_strName; }
            inline void setName(const char* name) { m_strName = name;}
        
        protected:
            void update(float delay);
        
        protected:
            std::string m_strName;
            NameToComponentList m_mapName2CompList;
        
        private:
            friend class Scene;
    };
}
