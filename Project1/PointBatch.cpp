#include "PointBatch.h"
#include "VertexManagement.h"

using namespace VertexManagement;

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
	CreateVertexArrayObject(VAOHandle);
	LoadVertexData(vertexBufferHandle, sizeof(PositionBundle), &positions[0], GL_STATIC_DRAW);
	BindToAttributes(shaderProgram);
}

void PointBatch::Render(ShaderProgram* shaderProgram)
{
	shaderProgram->Bind();
	glBindVertexArray(VAOHandle);
	
	glDrawArrays(GL_POINTS, 0, positions.size());

	glUseProgram(0);
	glBindVertexArray(0);
}

void PointBatch::RenderBatch(ShaderProgram* shaderProgram, int count)
{

}