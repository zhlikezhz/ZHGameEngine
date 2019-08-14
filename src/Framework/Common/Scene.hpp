#pragma once
#include <vector>

namespace ZH
{
    class Camera;
    class GameObject;
    class Scene
    {
        public:
            Scene();
            ~Scene();

            void setMainCamera(Camera* camera);
            inline Camera* getMainCamera() {return m_pMainCamera;}

            void addCamera(Camera* camera);
            void removeCamera(Camera* camera);
            void removeCameraByName(const char* name);
            Camera* getMainCameraByName(const char* name); 

            void addGameObject(GameObject* object);
            void removeGameObject(GameObject* object);
            void removeGameObjectByName(const char* name);
            GameObject* getGameObjectByName(const char* name);
            
            virtual void update(float delay);

        private:
            Camera* m_pMainCamera;
            std::vector<Camera*> m_vCameraList;
            std::vector<GameObject*> m_vGameObjectList;
    };
}