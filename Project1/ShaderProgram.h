#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

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

	map<string, mat4*> uniformMatrixPointers;
	map<string, Texture*> texturePointers;

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
	bool SetInstancedVertexVecFAttribute(const string& name, int size, int divisor);
	bool SetInstancedVertexMat4FAttribute(const string& name, int divisor);

	bool SetMat4FUniform(const string& name, const mat4* matrixPointer);
	bool SetScalIUniform(const string& name, int uniformValue);

	void AddUniformMatrix(const string& name, const mat4* matrixPointer);
	void AddTexture(const string& name, Texture* texturePointer);

	void UpdateShaderMatrices();
	void UpdateShaderTextures();
};