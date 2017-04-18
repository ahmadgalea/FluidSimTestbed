#pragma once

#include "ShaderProgram.h"
#include "PositionBundle.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

using namespace std;

namespace VertexManagement
{
	void LoadVertexData(GLuint& vertexBufferHandle, const GLuint& bufferSize, const void* pointerToVertices, const GLenum& vertexDrawMode);
	void CreateVertexArrayObject(GLuint& vertexArrayHandle);
	void CreateIndexArrays(vector<GLuint>& indexBufferHandles, vector<size_t> indexBufferSizes, vector<const void*> pointersToIndices);
	mat4* LoadMatrixData(GLuint& vertexBufferHandle, const GLuint& bufferSize);
	void WaitBuffer(GLsync& syncObject);
	void LockBuffer(GLsync& syncObject);
	void BindToAttribute(ShaderProgram* shaderProgram, const string& name, int size);
}
