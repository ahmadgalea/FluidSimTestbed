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
	if (vertexBufferHandle == -1)
	{
		glGenBuffers(1, &vertexBufferHandle);
	}

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

mat4* VertexManagement::LoadMatrixData(GLuint& vertexBufferHandle, const GLuint& bufferSize)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);

	// Allocate matrix buffer and flag as persistent.
	GLbitfield flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
	glBufferStorage(GL_ARRAY_BUFFER, bufferSize, 0, flags);

	return (mat4*)glMapBufferRange(GL_ARRAY_BUFFER, 0, bufferSize, flags); // Get persistent pointer to matrix buffer
}

void VertexManagement::WaitBuffer(GLsync& syncObject)
{
	GLenum waitReturn = GL_UNSIGNALED;

	while (waitReturn != GL_ALREADY_SIGNALED && waitReturn != GL_CONDITION_SATISFIED)
	{
		waitReturn = glClientWaitSync(syncObject, GL_SYNC_FLUSH_COMMANDS_BIT, 1);
	}
}

void VertexManagement::LockBuffer(GLsync& syncObject)
{
	if (syncObject)
	{
		glDeleteSync(syncObject);
	}

	syncObject = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
}

// Has been factored into ShaderProgram.h
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
