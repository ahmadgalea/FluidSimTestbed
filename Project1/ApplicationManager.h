#pragma once

#include "WindowManager.h"
#include "InputManager.h"

class ApplicationManager
{
private:

	WindowManager windowManager;
	InputManager inputManager;

	void InitialiseApplication();

public:
	ApplicationManager();
	~ApplicationManager();

	void ExecuteApplication();
	void ExecuteApplicationStages();
	void ErrorCallback(int, const char*); // Used for error detection by GLFW
};