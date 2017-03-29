
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
	shaderManager.LoadAllShaders();

	SetErrorCallback();
}

void ApplicationManager::ExecuteApplication()
{
	InitialiseApplication();
	windowManager.ExecuteMainLoop(this);
}

void ApplicationManager::ExecuteApplicationStages()
{

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