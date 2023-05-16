#ifndef __FRAMEWORK_CORE_MATERIAL__
#define __FRAMEWORK_CORE_MATERIAL__
#include "Core/Shader.hpp"
#include "glm/mat4x4.hpp"
#include <vector>

namespace UpPower
{
	class Texture;

	enum ShaderParameterType
    {
        BOOL,
        INT,
        UINT,
        FLOAT,
        TEXTURE,
        VECTOR3F,
        MATRIX4,
    };

	union ShaderParameterValue
    {
        bool valb;
        int vali;
        float valf;
        float val3f[3];
        unsigned int valui;
        Texture* texture;
        glm::mat4 mat4x4;
    };

	struct ShaderParameter
    {
        const char* name;
        ShaderParameterType type;
        ShaderParameterValue value;
        ShaderParameter(const char* name, ShaderParameterType type, ShaderParameterValue value)
        {
            this->name = name;
            this->type = type;
            this->value = value;
        }
    };

	typedef std::vector<ShaderParameter> ShaderParameterList;

	class Material
	{
	public:
		Material(Shader* shader);
		~Material();

		void DeleteValue(const char* name);
		void AddValue(const char* name, ShaderParameterType type, ShaderParameterValue value);
		const ShaderParameterList& GetShaderParameters();

		bool IsDirty();
		void SetDirty(bool dirty);

		Shader* GetShader();
		void SetShader(Shader* shader);

	protected:
		Material();
	
	private:
		bool m_bDirty;
		Shader* m_pShader;
		ShaderParameterList m_vShaderParameter;
	};
}

#endif