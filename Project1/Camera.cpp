#include "Camera.h"
#include <iostream>

Camera::Camera()
{
	windowManager = nullptr;
	viewMatrix = mat4(0.0f);
	projectionMatrix = mat4(0.0f);
	PVMatrix = mat4(0.0f);
	CalculatePVMatrix();
}

Camera::Camera(WindowManager* window) : windowManager(window)
{
	viewMatrix = mat4(0.0f);
	projectionMatrix = mat4(0.0f);
	PVMatrix = mat4(0.0f);
	CalculatePVMatrix();
}

Camera::Camera(WindowManager* window, const vec3& position, const vec3& center, const vec3& upAxis, const float& FOV, const float&  nearPlane, const float& farPlane) : windowManager(window)
{
	SetViewMatrix(position, center, upAxis);
	SetProjectioMatrix(FOV, nearPlane, farPlane);
	CalculatePVMatrix();
}

Camera::~Camera()
{
}

void Camera::SetViewMatrix(const vec3& position, const vec3& center, const vec3& upAxis)
{
	viewMatrix = lookAt(position, center, upAxis);
}

void Camera::SetProjectioMatrix(const float& FOV, const float&  nearPlane, const float& farPlane)
{
	projectionMatrix = perspective(FOV, ((float)windowManager->windowWidth) / ((float)windowManager->windowHeight), nearPlane, farPlane);
}

void Camera::CalculatePVMatrix()
{
	PVMatrix = projectionMatrix*viewMatrix;
}


mat4* Camera::GetPVMatrix() const
{
	return (mat4*)&PVMatrix;
}