#pragma once

#include "MeshShaderInterface.h"
#include "PointBatch.h"
#include "LineBatch.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;
using namespace glm;

class GridMesh : public MeshShaderInterface
{
private:

	PointBatch points;
	LineBatch lines;

	vec3 pointColour;
	float pointSize;
	vec3 lineColour;

public:
	GridMesh() {}
	GridMesh(const vec3& pntColour, const float& size, const vec3& linColour);
	~GridMesh() {}

	void AddVertex(const vec3& position);
	void AddLine(const vec3& position1, const vec3& position2);
	
	void SetPointColour(const vec3& colour);
	void SetPointSize(const float& size);
	void SetLineColour(const vec3& colour);

	void Update();
	void Render();
};
