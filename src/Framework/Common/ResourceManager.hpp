#pragma once
#include "IManager.hpp"

namespace ZH
{
    typedef int ResourceID;

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

            Asset* loadAsset(const char* name);
            Asset* getAsset(ResourceID id);
    };
}
