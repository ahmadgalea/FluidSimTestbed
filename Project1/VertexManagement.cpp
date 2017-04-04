#include "VertexManagement.h"

void VertexManagement::CreateVertexArrayObject(GLuint& vertexArrayHandle)
{
	GLenum ErrorCheckValue = glGetError();

	glGenVertexArrays(1, &vertexArrayHandle);
	glBindVertexArray(vertexArrayHandle);

	ErrorCheckValue = glGetError();

	if (ErrorCheckValue != GL_NO_ERROR) {
		fprintf(stderr, "ERROR: Could not create a VBO: %s \n", gluErrorString(ErrorCheckValue));
		// std::cout<<"Error in mesh initialization."<<std::endl;
		return;
	}
}

void VertexManagement::LoadVertexData(GLuint& vertexBufferHandle, const GLuint& bufferSize, const void* pointerToVertices, const GLenum& vertexDrawMode)
{

	GLenum ErrorCheckValue = glGetError();

	// Create vertex buffer
	glGenBuffers(1, &vertexBufferHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, pointerToVertices, vertexDrawMode);

	ErrorCheckValue = glGetError();

	if (ErrorCheckValue != GL_NO_ERROR) {
		fprintf(stderr, "ERROR: Could not create a VBO: %s \n", gluErrorString(ErrorCheckValue));
		// std::cout<<"Error in mesh initialization."<<std::endl;
		return;
	}
}

void VertexManagement::CreateIndexArrays(vector<GLuint>& indexBufferHandles, vector<size_t> indexBufferSizes, vector<const void*> pointersToIndices)
{

	GLenum ErrorCheckValue = glGetError();

	//Create index buffer
	glGenBuffers(indexBufferHandles.size(), &indexBufferHandles[0]);

	for (int index_array = 0; index_array < indexBufferHandles.size(); index_array++) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandles[index_array]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSizes[index_array], pointersToIndices[index_array], GL_STATIC_DRAW);
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandles[0]);

	ErrorCheckValue = glGetError();

	if (ErrorCheckValue != GL_NO_ERROR) {
		fprintf(stderr, "ERROR: Could not create index arrays: %s \n", gluErrorString(ErrorCheckValue));
		//std::cout<<"Error in mesh initialization."<<std::endl;
		return;
	}
}

void VertexManagement::BindToAttribute(ShaderProgram* shaderProgram, const string& name, int size)
{

	GLenum ErrorCheckValue = glGetError();
	
	int attribIndex = shaderProgram->GetAttributeLocation(name);
	
	glVertexAttribPointer(attribIndex, size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribIndex);

	ErrorCheckValue = glGetError();

	if (ErrorCheckValue != GL_NO_ERROR) {
		fprintf(stderr, "ERROR: Could not assign attribute indices: %s \n", gluErrorString(ErrorCheckValue));
		return;
	}
}
