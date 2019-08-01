#pragma once

namespace ZH
{
    class Texture 
    {
        public:
            static Texture* createTextureFromFile(const char* filePath);

            inline int getWidth() { return m_iWidth; }
            inline int getHeight() { return m_iHeight; }
            inline int getChannels() { return m_iChannels; }
            inline unsigned char* getTextureData() { return m_pTextrueData; }

        protected:
            bool loadImage(const char* filePath);
            void unloadImage();

        private:
            Texture();
            ~Texture();

        private:
            int m_iWidth;
            int m_iHeight;
            int m_iChannels;
            unsigned char* m_pTextrueData;
    };
}