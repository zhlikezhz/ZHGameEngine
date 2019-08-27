#pragma once
#include <map>
#include <vector>
#include <string>
#include "Scene.hpp"

namespace ZH
{
    class Component;
    class Camera;
    class GameObject
    {
        typedef std::vector<Component*> ComponentList;
        typedef std::map<std::string, ComponentList*> NameToComponentList;
        typedef std::vector<GameObject*> GObjectChildren;
        public:
            GameObject();
            ~GameObject();
            GameObject(std::string name);

            Component* addComponent(Component* comp);
            Component* addComponent(std::string name);

            template<class T>
            T* addComponent() {
                T* comp = new T; 
                addComponent(dynamic_cast<Component*>(comp));
                return comp;
            }

            void removeComponent(Component* comp);
            void removeComponents(std::string name);

            Component* getComponent(std::string name);
            std::vector<Component*> getComponents(std::string name);

            inline std::string getName() { return m_strName; }
            inline void setName(std::string name) { m_strName = name;}

            Camera* getCamera();

            void addChild(GameObject* object);
            void removeChild(GameObject* object);
            GameObject* getChild(const char* name);
            std::vector<GameObject*> getChildren();
            inline GameObject* getParent() { return m_pGObjectParent; }
            void setParent(GameObject* obj);

        protected:
            virtual void update();
            virtual void destroy();
        
        protected:
            std::string m_strName;
            GObjectChildren m_vGObjectChildren;
            NameToComponentList m_mapName2CompList;
            GameObject* m_pGObjectParent;
        
        private:
            friend class Scene;
    };
}
