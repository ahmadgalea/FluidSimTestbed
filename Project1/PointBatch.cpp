#include "PointBatch.h"
#include "VertexManagement.h"

#include <iostream>

using namespace VertexManagement;
using namespace std;

PointBatch::PointBatch()
{
	
}

PointBatch::~PointBatch()
{

}

void PointBatch::AddPoint(const vec3& position, const float& size, const vec3& colour)
{
	positions.push_back(PositionBundle(position, size));
	colours.push_back(colour);
}

void PointBatch::Compile(ShaderProgram* shaderProgram)
{
	if (VAOHandle == -1)
	{
		CreateVertexArrayObject(VAOHandle);
	}
	else
	{
		glBindVertexArray(VAOHandle);
	}
	// Make seperate buffers for positions and colours, bind these to attributes, and bind under single VAO.
	// an alternative would be to put both in a single buffer and include a 'step size' when binding to attributes.
	LoadVertexData(vertexBufferHandle, positions.size()*sizeof(PositionBundle), positions.data(), GL_STATIC_DRAW);
	shaderProgram->SetVertexAttribute("position", 4);
	LoadVertexData(colourBufferHandle, colours.size()*sizeof(vec3), colours.data(), GL_STATIC_DRAW);
	shaderProgram->SetVertexAttribute("colour", 3);
}

void PointBatch::Render(ShaderProgram* shaderProgram)
{
	shaderProgram->Bind();
	glBindVertexArray(VAOHandle);
	
	glPointSize(positions[0].size);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_POINTS, 0, positions.size());

	glUseProgram(0);
	glBindVertexArray(0);
}

void PointBatch::RenderBatch(ShaderProgram* shaderProgram, int count)
{
	shaderProgram->Bind();
	glBindVertexArray(VAOHandle);

	glPointSize(positions[0].size);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArraysInstanced(GL_POINTS, 0, positions.size(), count);

	glUseProgram(0);
	glBindVertexArray(0);
}