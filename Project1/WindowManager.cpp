

#include "WindowManager.h"

#include <iostream>
#include <string>
#include <functional>

#include "ApplicationManager.h"

using namespace std;
using namespace placeholders;


WindowManager::WindowManager()
{

}


void WindowManager::InitialiseWindow()
{

	windowWidth = 1920/2;
	windowHeight = 1080/2;
	windowName = "Fluid Sim Testbed";
	antiAliasing = 0;
	vsync = 0;

	// Initialize glfw
	if (!glfwInit()) {
		cout << "Failed to initialize GLFW" << endl;
		return;
	};

	// Create window object
	CreateWindow();

	// Initialize GLEW
	glewExperimental = true;  // Required for GLEW versions above 3.
	if (glewInit() != GLEW_OK) { //Initialize.
		cout << "Failed to initialize GLEW" << endl;
		return;
	}

	// because apparently GLEW initialization messses up the screen height.
	glfwSetWindowSize(window, windowWidth, windowHeight);

	function<void(GLFWwindow*, int, int)> onResize = bind(&WindowManager::OnResize, this, _1, _2, _3);
	typedef void(func)(GLFWwindow*, int, int);
	func* onResizeStatic = onResize.target<void(GLFWwindow*, int, int)>();
	glfwSetFramebufferSizeCallback(window, onResizeStatic);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

}

void WindowManager::OnResize(GLFWwindow* current_window, int width, int height)
{
	glfwSetWindowSize(window, width, height);
	glViewport(0, 0, width, height);
}

void WindowManager::CreateWindow()
{

	glfwWindowHint(GLFW_SAMPLES, antiAliasing); //Set antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Specifies to use GLFW v3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);

	if (window == NULL) {
		cout << "Failed to create window" << endl;
		glfwTerminate();
		return;
	};

	// Make window current, forces a pipeline flush
	glfwMakeContextCurrent(window);
	glfwSwapInterval(vsync);
	//glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	return;
}

GLFWwindow* WindowManager::GetWindowPointer() const
{
	return window;
}


void WindowManager::ExecuteMainLoop(ApplicationManager* applicationManager)
{

	// Draw window
	do {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		applicationManager->ExecuteApplicationStages();

		//swap buffers
		glfwSwapBuffers(window);
		//process all events in event cue
		glfwPollEvents();

	} // glfwGetKey returns GLFW_PRESS when GLFW_KEY_ESCAPE is pressed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}

WindowManager::~WindowManager()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
