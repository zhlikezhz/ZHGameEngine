#include <iostream>
#include "stb/lib_image.h"
#include "Core/Texture.hpp"
using namespace UpPower;

Texture::Texture()
:m_iWidth(0),
m_iHeight(0),
m_iColorChannel(0),
m_pTextureData(NULL)
{

}

Texture::~Texture()
{
	if (m_pTextureData != NULL)
	{
		stbi_image_free(m_pTextureData);
		m_pTextureData = NULL;
	}
}

Texture* Texture::CreateFromFile(const char* filename)
{
	Texture* texture = new Texture();
	texture->LoadFromFile(filename);
	if (texture->m_pTextureData == NULL)
	{
		delete texture;
		return nullptr;
	}
	return texture;
}

Texture* Texture::CreateFromMemory(const uchar* buffer, int length)
{
	Texture* texture = new Texture();
	texture->LoadFromMemory(buffer, length);
	if (texture->m_pTextureData == NULL)
	{
		delete texture;
		return nullptr;
	}
	return texture;
}

void Texture::LoadFromFile(const char* filename)
{
	m_pTextureData = stbi_load(filename, &m_iWidth, &m_iHeight, &m_iColorChannel, 0);
	if (m_pTextureData == NULL)
	{
		const char* err = stbi_failure_reason();
		std::cout << "ERROR::TEXTURE::" << err << std::endl;
	}
}

void Texture::LoadFromMemory(const uchar* buffer, int length)
{
	m_pTextureData = stbi_load_from_memory(buffer, length, &m_iWidth, &m_iHeight, &m_iColorChannel, 0);
	if (m_pTextureData == NULL)
	{
		const char* err = stbi_failure_reason();
		std::cout << "ERROR::TEXTURE::" << err << std::endl;
	}
}

int Texture::GetWidth()
{
	return m_iWidth;
}

int Texture::GetHeight()
{
	return m_iHeight;
}

int Texture::GetColorChannel()
{
	return m_iColorChannel;
}

const uchar* Texture::GetTextureData()
{
	return m_pTextureData;
}
