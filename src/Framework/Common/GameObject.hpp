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
        public:
            GameObject();
            ~GameObject();
            GameObject(std::string name);

            Component* addComponent(Component* comp);
            Component* addComponent(std::string name);

            template<class T>
            T* addComponent() {
                T* comp = new T; addComponent(dynamic_cast<Component*>(comp));
                return comp;
            }

            void removeComponent(Component* comp);
            void removeComponents(std::string name);

            Component* getComponent(std::string name);
            const std::vector<Component*>* getComponents(std::string name);

            inline std::string getName() { return m_strName; }
            inline void setName(std::string name) { m_strName = name;}

            inline void setCamera(Camera* camera) { m_pCamera = camera; }
            inline Camera* getCamera() {return m_pCamera;}

        protected:
            void update(float delay);
        
        protected:
            std::string m_strName;
            NameToComponentList m_mapName2CompList;
            Camera* m_pCamera;
        
        private:
            friend class Scene;
    };
}
