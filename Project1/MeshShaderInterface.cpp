#include "MeshShaderInterface.h"

void MeshShaderInterface::SetShaderProgram(ShaderProgram* program)
{
	shaderProgram = program;
}

void MeshShaderInterface::SetTexture(Texture* tex)
{
	texture = tex;
}

void MeshShaderInterface::SetShaderMatrixPointers(Camera* camera)
{
	PVMatrix = camera->GetPVMatrix();
	UpdatePVMMatrix();
	shaderProgram->AddShaderMatrix("ProjectionViewModel", &PVMMatrix);
}

void MeshShaderInterface::SetShaderTexturePointers()
{
	//shaderProgram-AddTexture("blue_car", texture);
}

void MeshShaderInterface::UpdateInterface()
{
	UpdatePVMMatrix();
	shaderProgram->UpdateShaderMatrices();
}

void MeshShaderInterface::SetScaleMatrix(const vec3& scaling)
{
	scaleMatrix = scale(mat4(1.0), scaling);
}
void MeshShaderInterface::SetRotationMatrix(const float& angleRads, const vec3& rotationAxis)
{
	rotationMatrix = rotate(mat4(1.0), angleRads, rotationAxis);
}
void MeshShaderInterface::SetTranslationMatrix(const vec3& translation)
{
	translationMatrix = translate(mat4(1.0), translation);
}
void MeshShaderInterface::UpdateModelMatrix()
{
	modelMatrix = translationMatrix*rotationMatrix*scaleMatrix;
}
void MeshShaderInterface::UpdateModelMatrix(const vec3& scaling, const float& angleRads, const vec3& rotationAxis, const vec3& translation)
{
	modelMatrix = mat4(1.0);
	modelMatrix = translate(modelMatrix, translation);
	modelMatrix = rotate(modelMatrix, angleRads, rotationAxis);
	modelMatrix = scale(modelMatrix, scaling);
}
void MeshShaderInterface::UpdateModelMatrix2D(const vec2& scaling, const float& angleRads, const vec2& translation)
{
	modelMatrix = mat4(1.0);
	modelMatrix = translate(modelMatrix, vec3(translation, 0.0f));
	modelMatrix = rotate(modelMatrix, angleRads, vec3(0.0f, 0.0f, 1.0f));
	modelMatrix = scale(modelMatrix, vec3(scaling, 0.0f));
}

void MeshShaderInterface::UpdatePVMMatrix()
{
	PVMMatrix = (*PVMatrix)*modelMatrix;
}