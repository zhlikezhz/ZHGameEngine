#pragma once
#include <vector>
#include <string>

namespace ZH
{
    class Camera;
    class GameObject;
    class Scene
    {
        public:
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

            void setName(std::string name) { m_strName = name; }
            std::string getName() { return m_strName; }
            
        protected:
            Scene();
            ~Scene();

            void init();
            void destroy();
            void start();
            void stop();
            void update();

            friend class SceneManager;

        private:
            Camera* m_pMainCamera;
            std::string m_strName;
            std::vector<Camera*> m_vCameraList;
            std::vector<GameObject*> m_vGameObjectList;
    };
}