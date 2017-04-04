#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct VertexP 
{
	GLfloat XYZW[4];
};

struct VertexPC 
{
	GLfloat XYZW[4];
	GLubyte RGBA[4];
};

struct VertexPCT 
{
	GLfloat XYZW[4];
	GLubyte RGBA[4];
	GLubyte STR[3];
};
