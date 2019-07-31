#include "Image.hpp"
#include "image/lib_image.h"
using namespace ZH;

Image::Image()
:m_iWidth(0),
m_iHeight(0),
m_iChannels(0),
m_pTextrueData(nullptr)
{

}

Image::~Image()
{
    unloadImage();
}

Image* Image::createImageFromFile(const char* filePath)
{
    Image* image = new Image;
    if (image->loadImage(filePath)) {
        return image;
    }
    delete image;
    return nullptr;
}

bool Image::loadImage(const char* filePath)
{
    m_pTextrueData = stbi_load(filePath, &m_iWidth, &m_iHeight, &m_iChannels, 0);
    return true;
}

void Image::unloadImage()
{
    stbi_image_free(m_pTextrueData);
}
