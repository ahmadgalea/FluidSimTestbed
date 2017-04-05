#include "GridMesh.h"

#include <map>
#include <string>
#include <iostream>

GridMesh::GridMesh(const vec3& pntColour, const float& size, const vec3& linColour)
{
	SetPointColour(pntColour);
	SetPointSize(size);
	SetLineColour(linColour);
}

void GridMesh::AddVertex(const vec3& position)
{
	if (points.positions.size() > 0)
	{
		vec3 lastPosition = points.positions.back().position;
		lines.AddLine(lastPosition, position, lineColour);
		lines.Compile(shaderProgram);
	}
	points.AddPoint(position, pointSize, pointColour);
	points.Compile(shaderProgram);
	
}

void GridMesh::AddLine(const vec3& position1, const vec3& position2)
{
	points.AddPoint(position1, pointSize, pointColour);
	points.AddPoint(position2, pointSize, pointColour);
	lines.AddLine(position1, position2, lineColour);

	points.Compile(shaderProgram);
	lines.Compile(shaderProgram);
}

void GridMesh::SetPointColour(const vec3& colour)
{
	pointColour = colour;
}

void GridMesh::SetPointSize(const float& size)
{
	pointSize = size;
}

void GridMesh::SetLineColour(const vec3& colour)
{
	lineColour = colour;
}

void GridMesh::Update()
{
	UpdateModelMatrix2D(vec2(1.0f, 2.0f), 2.0f, vec2(0.0f, 0.0f));
	UpdateInterface();
}

void GridMesh::Render()
{
	if (shaderProgram != nullptr)
	{
		points.Render(shaderProgram);
		lines.Render(shaderProgram);
	}
}
