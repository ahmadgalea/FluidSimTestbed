
#include <functional>
#include <iostream>

#include "ApplicationManager.h"

using namespace placeholders;

ApplicationManager::ApplicationManager()
{
}

ApplicationManager::~ApplicationManager()
{

}

void ApplicationManager::InitialiseApplication()
{
	windowManager.InitialiseWindow();
	inputManager.InitialiseInputHandling(windowManager.GetWindowPointer());

	camera = Camera(&windowManager, vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), radians(45.0f), 0.0f, 100.0f);

	SetErrorCallback();

	shaderManager.LoadAllShaders();
	textureManager.LoadAllTextures();

	gridMesh = GridMesh(vec3(1.0f, 1.0f, 1.0f), 6.0f, vec3(0.0f, 1.0f, 0.0f));
	gridMesh.SetShaderProgram(shaderManager.GetProgramFromName("SimpleVertexSimpleFragment"));
	gridMesh.SetShaderMatrixPointers(&camera);

	gridMesh.AddVertex(vec3(-0.5, -0.5, 0.0));
	gridMesh.AddVertex(vec3(0.5, -0.5, 0.0));
	gridMesh.AddVertex(vec3(0.5, 0.5, 0.0));
	gridMesh.AddVertex(vec3(-0.5, 0.5, 0.0));
	gridMesh.AddVertex(vec3(-0.5, -0.5, 0.0));
	
	//triangles.AddTrianglePositions(vec3(-0.2, -0.2, 0.0), vec3(0.2, -0.2, 0.0), vec3(0.0, 0.2, 0.0));
	//triangles.AddTriangleColour(vec3(0.0, 0.0, 1.0));
	//triangles.Compile(shaderManager.GetProgramFromName("SimpleVertexSimpleFragment"));
}

void ApplicationManager::ExecuteApplication()
{
	InitialiseApplication();
	windowManager.ExecuteMainLoop(this);
}

void ApplicationManager::ExecuteApplicationStages()
{
	gridMesh.Update();
	gridMesh.Render();
	//triangles.Render(shaderManager.GetProgramFromName("SimpleVertexSimpleFragment"));
}


void ApplicationManager::SetErrorCallback()
{
	function<void(int, const char*)> errorCallback = bind(&ApplicationManager::ErrorCallback, this, _1, _2);
	typedef void(func)(int, const char*);
	func* errorCallbackStatic = errorCallback.target<void(int, const char*)>();
	glfwSetErrorCallback(errorCallbackStatic);
}
void ApplicationManager::ErrorCallback(int error, const char* description)
{
	fputs(description, stderr);
}