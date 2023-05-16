#ifndef __FRAMEWORK_CORE_TEXTURE__
#define __FRAMEWORK_CORE_TEXTURE__
#include "Core/TypeDefine.hpp"

namespace UpPower
{
	class Texture
	{
	public:
		int GetWidth();
		int GetHeight();
		int GetColorChannel();
		const uchar * GetTextureData();

		static Texture* CreateFromFile(const char* filename);
		static Texture* CreateFromMemory(const uchar* buffer, int length);

	protected:
		Texture();
		~Texture();
		void LoadFromFile(const char* filename);
		void LoadFromMemory(const uchar* buffer, int length);

	protected:
		int m_iWidth;
		int m_iHeight;
		int m_iColorChannel;
		uchar* m_pTextureData;
	};
}

#endif