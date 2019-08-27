#pragma once
#include <string>
#include "Asset.hpp"
#include "IManager.hpp"

namespace ZH
{
    class Mesh;
    class Texture;
    class ResourceManager : public IManager<ResourceManager>
    {
        protected:
            ResourceManager();
            ~ResourceManager();
        
        public:
            virtual void init();
            virtual void destroy();

            template<class T>
            T* loadAsset(std::string name) {

            }

            template<class T>
            T* getAsset(std::string name) {

            }

            template<class T>
            T* getAsset(AssetID id) {

            }

            Asset* loadAsset(Asset* asset) {

            }
    };
}
