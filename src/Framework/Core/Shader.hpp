#ifndef __UPPOWER_SHADER__
#define __UPPOWER_SHADER__

namespace UpPower
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		void Use();
		void AddVBO(const void* vboBuffer, size_t vboSize);
		void AddVBO(const void* vboBuffer, size_t vboSize, const void* eboBuffer, size_t eboSize);
		void AddTexture();
		void SetShader(const char* vertex, const char* fragment);
	private:
		unsigned int m_uiVAO = -1;
		unsigned int m_uiShaderProgram = -1;
	};
}

#endif