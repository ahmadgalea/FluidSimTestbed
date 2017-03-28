#pragma once

#include "GL\glew.h"
#include "GLFW\glfw3.h"

class InputManager
{
public:
	InputManager() {}
	~InputManager() {}

	void InitialiseInputHandling(GLFWwindow* window);
};