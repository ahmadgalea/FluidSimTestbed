#pragma once

#include "ShaderProgram.h"
#include "PositionBundle.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

using namespace glm;
using namespace std;

class PointBatch
{
public:
	vector<PositionBundle> positions;
	vector<vec3> colours;
private:
	GLuint VAOHandle = -1;
	GLuint vertexBufferHandle = -1;
	GLuint colourBufferHandle = -1;

	GLsync syncObject;

public:
	PointBatch();
	~PointBatch();

	void AddPoint(const vec3& position, const float& size, const vec3& colour);
	void Compile(ShaderProgram* shaderProgram);

	void Render(ShaderProgram* shaderProgram);
	void RenderBatch(ShaderProgram* shaderProgram, int count);
};
