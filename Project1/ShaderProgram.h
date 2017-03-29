#pragma once

#include "Shader.h"

class ShaderProgram
{
public:
	Shader* vertexShader = nullptr;
	Shader* fragmentShader = nullptr;
	Shader* geometryShader = nullptr;
	Shader* computeShader = nullptr;

	GLuint programID;
	string programName;

public:
	ShaderProgram(Shader* vertexShader, Shader* fragmentShader);
	ShaderProgram(Shader* vertexShader, Shader* fragmentShader, Shader* geometryShader);
	ShaderProgram(Shader* vertexShader, Shader* fragmentShader, Shader* geometryShader, Shader* computeShader);
	~ShaderProgram();

	void LinkProgram();

	void Bind();
};