
#include "InputManager.h"

void InputManager::InitialiseInputHandling(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
}