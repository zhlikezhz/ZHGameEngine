#pragma once
#include <vector>
#include "Texture.hpp"

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
    };

    union ShaderParameterValue
    {
        bool valb;
        int vali;
        float valf;
        float val3f[3];
        unsigned int valui;
        Texture* texture;
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
            Material();
            ~Material();

            inline void addValue(const char* name, ShaderParameterType type, ShaderParameterValue value) {
                m_vShaderParameter.push_back(ShaderParameter(name, type, value));
                if (ShaderParameterType::TEXTURE == type) {
                    setDirty(true);
                }
            }
            inline const ShaderParameterList& getShaderParameters() {
                return m_vShaderParameter;
            }
            inline bool isDirty() {return m_bDirty;}
            inline void setDirty(bool dirty) {m_bDirty = dirty;}

        private:
            bool m_bDirty;
            ShaderParameterList m_vShaderParameter;
    };
}