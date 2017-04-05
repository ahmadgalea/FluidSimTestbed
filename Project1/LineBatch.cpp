#include "LineBatch.h"
#include "VertexManagement.h"

#include <iostream>

using namespace VertexManagement;
using namespace std;

LineBatch::LineBatch()
{
	
}

LineBatch::~LineBatch()
{

}

void LineBatch::AddLine(const vec3& position1, const vec3& position2, const vec3& colour1, const vec3& colour2)
{
	positions.push_back(position1);
	positions.push_back(position2);
	colours.push_back(colour1);
	colours.push_back(colour2);
	lineCount++;
}

void LineBatch::AddLine(const vec3& position1, const vec3& position2, const vec3& colour)
{
	positions.push_back(position1);
	positions.push_back(position2);
	colours.push_back(colour);
	colours.push_back(colour);
	lineCount++;
}

void LineBatch::Compile(ShaderProgram* shaderProgram)
{
	if (VAOHandle == -1)
	{
		CreateVertexArrayObject(VAOHandle);
	}
	else
	{
		glBindVertexArray(VAOHandle);
	}

	LoadVertexData(vertexBufferHandle, positions.size() * sizeof(vec3), positions.data(), GL_STATIC_DRAW);
	shaderProgram->SetVertexAttribute("position", 3);
	LoadVertexData(colourBufferHandle, colours.size() * sizeof(vec3), colours.data(), GL_STATIC_DRAW);
	shaderProgram->SetVertexAttribute("colour", 3);
}

void LineBatch::Render(ShaderProgram* shaderProgram)
{
	shaderProgram->Bind();
	glBindVertexArray(VAOHandle);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_LINES, 0, positions.size());

	glUseProgram(0);
	glBindVertexArray(0);
}

void LineBatch::RenderBatch(ShaderProgram* shaderProgram, int count)
{
	shaderProgram->Bind();
	glBindVertexArray(VAOHandle);

	glDrawArraysInstanced(GL_LINES, 0, positions.size(), count);

	glUseProgram(0);
	glBindVertexArray(0);
}