#pragma once

#include <string>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

using namespace std;

class ApplicationManager;

class WindowManager
{
public:

	GLint windowWidth, windowHeight, antiAliasing, vsync;
	string windowName;

	GLFWwindow* window;

	WindowManager();
	~WindowManager();

	void InitialiseWindow();
	void CreateWindow();
	GLFWwindow* GetWindowPointer() const;
	void ExecuteMainLoop(ApplicationManager* applicationManager);

	void OnResize(GLFWwindow*, int, int); // Used for window resizing.
};