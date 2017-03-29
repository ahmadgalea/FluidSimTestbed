#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

class Camera
{
public:

	mat4 viewMatrix;
	mat4 projectionMatrix;
};