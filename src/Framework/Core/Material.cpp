#include <vector>
#include "Core/Material.hpp"
#include "Core/Texture.hpp"
#include "Core/Shader.hpp"
#include "glm/mat4x4.hpp"
using namespace UpPower;

Material::Material()
:m_bDirty(false),
m_pShader(nullptr),
m_vShaderParameter()
{

}

Material::Material(Shader* shader)
:m_bDirty(false),
m_pShader(shader),
m_vShaderParameter()
{

}

Material::~Material()
{
	m_vShaderParameter.clear();
}

void Material::AddValue(const char* name, ShaderParameterType type, ShaderParameterValue value)
{
	DeleteValue(name);
	m_vShaderParameter.push_back(ShaderParameter(name, type, value));
	if (ShaderParameterType::TEXTURE == type) 
	{
		SetDirty(true);
	}
}

void Material::DeleteValue(const char* name) 
{
	for (ShaderParameterList::const_iterator iter = m_vShaderParameter.cbegin(); iter != m_vShaderParameter.cend(); iter++) 
	{
		if (iter->name == name) 
		{
			m_vShaderParameter.erase(iter);
			return;
		}
	}
}

const ShaderParameterList& Material::GetShaderParameters() 
{
	return m_vShaderParameter;
}

bool Material::IsDirty() 
{
	return m_bDirty;
}

void Material::SetDirty(bool dirty) 
{
	m_bDirty = dirty;
}

Shader* Material::GetShader() 
{ 
	return m_pShader; 
}

void Material::SetShader(Shader* shader)
{
	m_pShader = shader;
	SetDirty(true);
}