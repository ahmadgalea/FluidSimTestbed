#pragma once

#include "WindowManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "Camera.h"

#include "GridMesh.h"
#include "TriangleBatch.h"

class ApplicationManager
{
private:

	WindowManager windowManager;
	InputManager inputManager;
	ShaderManager shaderManager;
	TextureManager textureManager;

	Camera camera;

	GridMesh gridMesh;
	//TriangleBatch triangles;

	void InitialiseApplication();

public:
	ApplicationManager();
	~ApplicationManager();

	void ExecuteApplication();
	void ExecuteApplicationStages();

	void SetErrorCallback();
	void ErrorCallback(int, const char*); // Used for error detection by GLFW
};