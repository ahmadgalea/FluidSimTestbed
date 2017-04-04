#pragma once

#include "WindowManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "PointBatch.h"
#include "LineBatch.h"
#include "TriangleBatch.h"

class ApplicationManager
{
private:

	WindowManager windowManager;
	InputManager inputManager;
	ShaderManager shaderManager;
	TextureManager textureManager;

	PointBatch points;
	LineBatch lines;
	TriangleBatch triangles;

	void InitialiseApplication();

public:
	ApplicationManager();
	~ApplicationManager();

	void ExecuteApplication();
	void ExecuteApplicationStages();

	void SetErrorCallback();
	void ErrorCallback(int, const char*); // Used for error detection by GLFW
};