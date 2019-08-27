#pragma once

namespace ZH
{
    typedef int AssetID;

    class Asset
    {
        public:
            inline AssetID getAssetID() { return m_iAssetID; }
        
        private:
            Asset() {}

            ~Asset() {}

            inline void setAssetID(AssetID id) { m_iAssetID = id;}
        
        protected:
            AssetID m_iAssetID;

        private:
            friend class ResourceManager;
    };
}