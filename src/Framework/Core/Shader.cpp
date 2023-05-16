#include <cstdio>
#include <assert.h>
#include <iostream>
#include "glad/glad.h"
#include "Core/Shader.hpp"
using namespace UpPower;

Shader::Shader()
{
	m_uiShaderProgram = -1;
}

Shader::~Shader()
{
	if (m_uiShaderProgram != -1)
	{
		glDeleteProgram(m_uiShaderProgram);
	}
}

void Shader::SetShader(const char* vertex, const char* fragment)
{
    // 编译和链接OpenGL着色器程序
    assert(vertex != nullptr);
    assert(fragment != nullptr);

    unsigned int vertexShader = -1;
    unsigned int fragmentShader = -1;

    try
    {
        // 如果已经存在一个着色器程序对象，则删除它
        if (m_uiShaderProgram != -1)
        {
            glDeleteProgram(m_uiShaderProgram);
            m_uiShaderProgram = -1;
        }

        // 编译顶点着色器
        int success;
        char infoLog[512];

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertex, NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
            throw std::runtime_error("Failed to compile vertex shader: " + std::string(infoLog));
        }

        // 编译片元着色器
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragment, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
            throw std::runtime_error("Failed to compile fragment shader: " + std::string(infoLog));
        }

        // 链接着色器程序
        m_uiShaderProgram = glCreateProgram();
        glAttachShader(m_uiShaderProgram, vertexShader);
        glAttachShader(m_uiShaderProgram, fragmentShader);
        glLinkProgram(m_uiShaderProgram);
        glGetProgramiv(m_uiShaderProgram, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(m_uiShaderProgram, sizeof(infoLog), NULL, infoLog);
            throw std::runtime_error("Failed to link shader program: " + std::string(infoLog));
        }

        // 清理
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
    }
    catch (const std::exception& e)
    {
        if (fragmentShader != -1)
            glDeleteShader(fragmentShader);

        if (vertexShader != -1)
            glDeleteShader(vertexShader);

        if (m_uiShaderProgram != -1)
        {
            glDeleteProgram(m_uiShaderProgram);
            m_uiShaderProgram = -1;
        }

        std::cout << "ERROR::SHADER::" << e.what() << std::endl;
        throw;
    }
}

void Shader::Use()
{
	assert(m_uiShaderProgram != -1);
	glUseProgram(m_uiShaderProgram);
}