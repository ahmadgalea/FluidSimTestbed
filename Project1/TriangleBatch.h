#pragma once

#include "ShaderProgram.h"
#include "PositionBundle.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

class TriangleBatch
{
public:
	vector<vec3> positions;
	vector<vec3> colours;
	vector<vec2> UVs;
private:
	GLuint VAOHandle = -1;
	GLuint vertexBufferHandle = -1;;
	GLuint colourBufferHandle = -1;
	GLuint UVBufferHandle = -1;

	int lineCount = 0;

public:
	TriangleBatch();
	~TriangleBatch();

	void AddTrianglePositions(const vec3& position1, const vec3& position2, const vec3& position3);
	void AddTriangleColours(const vec3& colour1, const vec3& colour2, const vec3& colour3);
	void AddTriangleColour(const vec3& colour);
	void AddTriangleUVs(const vec3& UV1, const vec3& UV2);
	void Compile(ShaderProgram* shaderProgram);

	void Render(ShaderProgram* shaderProgram);
	void RenderBatch(ShaderProgram* shaderProgram, int count);
};