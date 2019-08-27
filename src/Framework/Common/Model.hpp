#pragma once
#include "GameObject.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace ZH
{
    class Mesh;
    class Transform;
    class Model : public GameObject
    {
        public:
            Model();
            Model(std::string path);
            ~Model();

            void init();
            void initWithFile(std::string path);

            static Model* createModel(std::string path);
        
        private:
            void processNode(aiNode* node, const aiScene *scene);
            Model* processMesh(aiMesh* mesh,  const aiScene *scene);
        
        private:
            std::string m_strPath;
            Transform* transform;
    };
}