#pragma once

#include "Shader.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <map>
#include <string>

using namespace glm;
using namespace std;

class ShaderProgram
{
public:
	Shader* vertexShader = nullptr;
	Shader* fragmentShader = nullptr;
	Shader* geometryShader = nullptr;
	Shader* computeShader = nullptr;

	GLuint programID;
	string programName;

	map<string, mat4*> matrixPointers;

public:
	ShaderProgram(Shader* vertexShader, Shader* fragmentShader);
	ShaderProgram(Shader* vertexShader, Shader* fragmentShader, Shader* geometryShader);
	ShaderProgram(Shader* vertexShader, Shader* fragmentShader, Shader* geometryShader, Shader* computeShader);
	~ShaderProgram();

	void LinkProgram();

	void Bind();

	GLint GetAttributeLocation(const string& name) const;
	GLint GetUniformLocation(const string& name) const;

	bool SetVertexAttribute(const string& name, int size);
	bool SetMat4FUniform(const string& name, const mat4* matrixPointer);
	bool SetMat1IUniform(const string& name, int uniformValue);

	void UpdateShaderMatrices();
};