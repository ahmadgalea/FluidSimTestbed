#pragma once

#include "WindowManager.h"
#include "InputManager.h"
#include "ShaderManager.h"

class ApplicationManager
{
private:

	WindowManager windowManager;
	InputManager inputManager;
	ShaderManager shaderManager;

	void InitialiseApplication();

public:
	ApplicationManager();
	~ApplicationManager();

	void ExecuteApplication();
	void ExecuteApplicationStages();
	void ErrorCallback(int, const char*); // Used for error detection by GLFW
};