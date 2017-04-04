#include "TriangleBatch.h"
#include "VertexManagement.h"

#include <iostream>

using namespace VertexManagement;
using namespace std;

TriangleBatch::TriangleBatch()
{

}

TriangleBatch::~TriangleBatch()
{

}

void TriangleBatch::AddTrianglePositions(const vec3& position1, const vec3& position2, const vec3& position3)
{
	positions.push_back(position1);
	positions.push_back(position2);
	positions.push_back(position3);
}

void TriangleBatch::AddTriangleColours(const vec3& colour1, const vec3& colour2, const vec3& colour3)
{
	colours.push_back(colour1);
	colours.push_back(colour2);
	colours.push_back(colour3);
}
void TriangleBatch::AddTriangleColour(const vec3& colour)
{
	colours.push_back(colour);
	colours.push_back(colour);
	colours.push_back(colour);
}
void TriangleBatch::AddTriangleUVs(const vec3& UV1, const vec3& UV2)
{
	UVs.push_back(UV1);
	UVs.push_back(UV2);
}

void TriangleBatch::Compile(ShaderProgram* shaderProgram)
{
	CreateVertexArrayObject(VAOHandle);

	LoadVertexData(vertexBufferHandle, positions.size() * sizeof(vec3), positions.data(), GL_STATIC_DRAW);
	BindToAttribute(shaderProgram, "position", 3);
	LoadVertexData(colourBufferHandle, colours.size() * sizeof(vec3), colours.data(), GL_STATIC_DRAW);
	BindToAttribute(shaderProgram, "colour", 3);
	LoadVertexData(UVBufferHandle, UVs.size() * sizeof(vec3), UVs.data(), GL_STATIC_DRAW);
	BindToAttribute(shaderProgram, "UV", 2);
}

void TriangleBatch::Render(ShaderProgram* shaderProgram)
{
	shaderProgram->Bind();
	glBindVertexArray(VAOHandle);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_TRIANGLES, 0, positions.size());

	glUseProgram(0);
	glBindVertexArray(0);
}

void TriangleBatch::RenderBatch(ShaderProgram* shaderProgram, int count)
{
	shaderProgram->Bind();
	glBindVertexArray(VAOHandle);

	glDrawArraysInstanced(GL_TRIANGLES, 0, positions.size(), count);

	glUseProgram(0);
	glBindVertexArray(0);
}