#ifndef __FRAMEWORK_CORE_RENDER__
#define __FRAMEWORK_CORE_RENDER__
#include "Core/TypeDefine.hpp"
#include <Map>

namespace UpPower
{
	class Material;

	class Render
	{
	public:
		Render();
		~Render();
		void DoRender();

	protected:
		uint m_uiUV1VBO;
		uint m_uiUV2VBO;
		uint m_uiVertexVBO;
		uint m_uiVertexColorVBO;
		uint m_uiNormalVBO;
		uint m_uiTriangleEBO;
		Material* m_pMaterial;
	};
}

#endif