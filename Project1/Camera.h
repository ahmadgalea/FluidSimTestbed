#pragma once

#include "WindowManager.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

class Camera
{
private:
	WindowManager* windowManager;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 PVMatrix;

public:
	Camera();
	Camera(WindowManager* window);
	Camera(WindowManager* window, const vec3& position, const vec3& center, const vec3& upAxis, const float& FOV, const float&  nearPlane, const float& farPlane);
	~Camera();

	void SetViewMatrix(const vec3& position, const vec3& center, const vec3& upAxis);
	void SetProjectioMatrix(const float& FOV, const float&  nearPlane, const float& farPlane);
	void CalculatePVMatrix();
	mat4* GetPVMatrix() const;
};