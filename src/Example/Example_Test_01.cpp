#include <cstdio>
#include <iostream>
#include "Example_Test_01.hpp"

const char *g_vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *g_fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";


Example_Test_01::Example_Test_01()
{

}

void Example_Test_01::DoInit()
{
	float vertices1[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	float vertices2[] = {
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.0f, -0.5f, 0.0f
	};

	glGenVertexArrays(1, &m_uiVAO);

	GLuint VBO[2];
	glGenBuffers(2, VBO);
	glBindVertexArray(m_uiVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

	glBindVertexArray(m_uiVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

	m_ptrShader = new UpPower::Shader();
	m_ptrShader->SetShader(g_vertexShaderSource, g_fragmentShaderSource);
}


void Example_Test_01::DoUpdate()
{
	m_ptrShader->Use();
	glBindVertexArray(m_uiVAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 1, 3);
}

void Example_Test_01::DoDestory()
{
	fprintf(stdout, "DoDestory");
}