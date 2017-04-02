#pragma once

#include "WindowManager.h"
#include "InputManager.h"
#include "ShaderManager.h"

#include "PointBatch.h"

class ApplicationManager
{
private:

	WindowManager windowManager;
	InputManager inputManager;
	ShaderManager shaderManager;

	PointBatch points;

	void InitialiseApplication();

public:
	ApplicationManager();
	~ApplicationManager();

	void ExecuteApplication();
	void ExecuteApplicationStages();

	void SetErrorCallback();
	void ErrorCallback(int, const char*); // Used for error detection by GLFW
};