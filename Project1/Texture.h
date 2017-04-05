#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SOIL.h"

using namespace std;

class Texture
{
private:
	int width, height;
	unsigned char* pixelData;

	GLuint textureID;

public:
	GLuint textureUnit;

public:
	Texture() : width(0), height(0) {}
	Texture(const string& fileName, GLenum imageFormat = SOIL_LOAD_RGBA);
	~Texture();

	void Bind();
};