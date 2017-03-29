#pragma once

#include <string>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

using namespace std;

enum class ShaderType
{
	VertexShader,
	FragmentShader,
	GeometryShader,
	ComputeShader
};

class Shader
{
public:
	GLuint shaderID;
	ShaderType type;
	
	string name;

public:
	Shader() : shaderID(0) {}
	Shader(ShaderType type, const string& shaderName);

	~Shader();

};