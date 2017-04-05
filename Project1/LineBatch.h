#pragma once

#include "ShaderProgram.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

using namespace glm;
using namespace std;
class LineBatch
{
public:
	vector<vec3> positions;
	vector<vec3> colours;
private:
	GLuint VAOHandle = -1;
	GLuint vertexBufferHandle = -1;;
	GLuint colourBufferHandle = -1;

	int lineCount = 0;

public:
	LineBatch();
	~LineBatch();

	void AddLine(const vec3& position1, const vec3& position2, const vec3& colour1, const vec3& colour2);
	void AddLine(const vec3& position1, const vec3& position2, const vec3& colour);
	void Compile(ShaderProgram* shaderProgram);

	void Render(ShaderProgram* shaderProgram);
	void RenderBatch(ShaderProgram* shaderProgram, int count);

};