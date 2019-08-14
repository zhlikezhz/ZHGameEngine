// #pragma once
#ifndef ZH_MATERIAL
#define ZH_MATERIAL
#include <vector>
#include "Texture.hpp"
#include "glm/mat4x4.hpp"
#include "Component.hpp"
#include "Shader.hpp"

namespace ZH
{
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

    class Material : public Component
    {
        DECLARE_CLASS(Material)

        public:
            Material();
            ~Material();

            inline void addValue(const char* name, ShaderParameterType type, ShaderParameterValue value) {
                deleteValue(name);
                m_vShaderParameter.push_back(ShaderParameter(name, type, value));
                if (ShaderParameterType::TEXTURE == type) {
                    setDirty(true);
                }
            }
            inline void deleteValue(const char* name) {
                for (ShaderParameterList::const_iterator iter = m_vShaderParameter.cbegin(); iter != m_vShaderParameter.cend(); iter++) {
                    if (iter->name == name) {
                        m_vShaderParameter.erase(iter);
                        return;
                    }
                }
            }
            inline const ShaderParameterList& getShaderParameters() {
                return m_vShaderParameter;
            }
            inline bool isDirty() {return m_bDirty;}
            inline void setDirty(bool dirty) {m_bDirty = dirty;}

            inline Shader* getShader() { return m_pShader; }
            inline void setShader(Shader* shader) {
                m_pShader = shader;
                setDirty(true);
            }

        private:
            bool m_bDirty;
            Shader* m_pShader;
            ShaderParameterList m_vShaderParameter;
    };

}
#endif