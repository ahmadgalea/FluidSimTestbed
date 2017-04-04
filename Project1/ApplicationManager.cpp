
#include <functional>

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

	SetErrorCallback();

	shaderManager.LoadAllShaders();
	textureManager.LoadAllTextures();

	points.AddPoint(vec3(-0.5, -0.5, 0.0), 0, vec3(1.0, 1.0, 1.0));
	points.AddPoint(vec3(-0.5, 0.5, 0.0), 0, vec3(1.0, 1.0, 1.0));
	points.AddPoint(vec3(0.5, -0.5, 0.0), 0, vec3(1.0, 1.0, 1.0)); 
	points.AddPoint(vec3(0.5, 0.5, 0.0), 0, vec3(1.0, 1.0, 1.0));

	points.Compile(shaderManager.GetProgramFromName("SimpleVertexSimpleFragment"));

	lines.AddLine(vec3(-0.5, -0.5, 0.0), vec3(-0.5, 0.5, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0));
	lines.AddLine(vec3(-0.5, -0.5, 0.0), vec3(0.5, -0.5, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0));
	lines.AddLine(vec3(0.5, 0.5, 0.0), vec3(-0.5, 0.5, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0));
	lines.AddLine(vec3(0.5, 0.5, 0.0), vec3(0.5, -0.5, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0));

	lines.Compile(shaderManager.GetProgramFromName("SimpleVertexSimpleFragment"));

	triangles.AddTrianglePositions(vec3(-0.2, -0.2, 0.0), vec3(0.2, -0.2, 0.0), vec3(0.0, 0.2, 0.0));
	triangles.AddTriangleColour(vec3(0.0, 0.0, 1.0));
	triangles.Compile(shaderManager.GetProgramFromName("SimpleVertexSimpleFragment"));
}

void ApplicationManager::ExecuteApplication()
{
	InitialiseApplication();
	windowManager.ExecuteMainLoop(this);
}

void ApplicationManager::ExecuteApplicationStages()
{
	points.Render(shaderManager.GetProgramFromName("SimpleVertexSimpleFragment"));
	lines.Render(shaderManager.GetProgramFromName("SimpleVertexSimpleFragment"));
	triangles.Render(shaderManager.GetProgramFromName("SimpleVertexSimpleFragment"));
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