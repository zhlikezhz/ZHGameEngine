#pragma once
#include "Example.hpp"
#include "glad/glad.h"
#include "Core/Shader.hpp"

class Example_Test_01 : public Example
{
public:
	Example_Test_01();

	virtual void DoInit();
	virtual void DoUpdate();
	virtual void DoDestory();

private:
	unsigned int m_uiVAO;
	UpPower::Shader* m_ptrShader;
};