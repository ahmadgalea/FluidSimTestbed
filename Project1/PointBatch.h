#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

using namespace glm;
using namespace std;

class PosBundle
{
	vec3 position;
	float size;
	PosBundle(vec3 pos, float size1) : position(pos), size(size1) {}
};

class PointBatch
{
public:
	vector<PosBundle> positions
};
