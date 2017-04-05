#pragma once

#include "ShaderProgram.h"
#include "PointBatch.h"
#include "LineBatch.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
using namespace glm;

class MeshShaderInterface
{
protected:
	ShaderProgram* shaderProgram = nullptr;

	mat4 scaleMatrix = mat4(1.0f);
	mat4 rotationMatrix = mat4(1.0f);
	mat4 translationMatrix = mat4(1.0f);
	mat4 modelMatrix = mat4(1.0f);

	mat4* PVMatrix;
	mat4 PVMMatrix;

public:
	MeshShaderInterface() {}
	~MeshShaderInterface() {}

	void SetScaleMatrix(const vec3& scaling);
	void SetRotationMatrix(const float& angleRads, const vec3& rotationAxis);
	void SetTranslationMatrix(const vec3& translation);
	void UpdateModelMatrix();
	void UpdateModelMatrix(const vec3& scaling, const float& angleRads, const vec3& rotationAxis, const vec3& translation);
	void UpdateModelMatrix2D(const vec2& scaling, const float& angleRads, const vec2& translation);

	void UpdatePVMMatrix();

	void SetShaderProgram(ShaderProgram* program);
	void SetShaderMatrixPointers(Camera* camera);

	void UpdateInterface();
};

