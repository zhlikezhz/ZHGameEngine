#pragma once
#include "Scene.hpp"
#include "IManager.hpp"

namespace ZH
{
    class SceneManager : public IManager<SceneManager>
    {
        typedef std::vector<Scene*> SceneList;

        public:
            SceneManager();
            ~SceneManager();

            Scene* getScene(std::string name);
            Scene* createScene(std::string name);
            void deleteScene(Scene* scene);
            Scene* getMainScene();
            void changeScene(Scene* scene);

            virtual void init();
            virtual void destroy();
            virtual void update();

        private:
            Scene* m_pMainScene;
            SceneList m_vSceneList;
        
    };
}