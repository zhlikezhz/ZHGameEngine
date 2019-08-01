#include "Texture.hpp"
#include "image/lib_image.h"
using namespace ZH;

Texture::Texture()
:m_iWidth(0),
m_iHeight(0),
m_iChannels(0),
m_pTextrueData(nullptr)
{

}

Texture::~Texture()
{
    unloadImage();
}

Texture* Texture::createTextureFromFile(const char* filePath)
{
    Texture* image = new Texture;
    if (image->loadImage(filePath)) {
        return image;
    }
    delete image;
    return nullptr;
}

bool Texture::loadImage(const char* filePath)
{
    m_pTextrueData = stbi_load(filePath, &m_iWidth, &m_iHeight, &m_iChannels, 0);
    return true;
}

void Texture::unloadImage()
{
    stbi_image_free(m_pTextrueData);
}
