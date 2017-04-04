#include "Shader.h"
#include "GlobalIOUtilities.h"

Shader::Shader(ShaderType shaderType, const string& shaderName) : type(shaderType), name(shaderName)
{
	string filename;

	switch (shaderType)
	{
	case ShaderType::VertexShader:
		filename = GetBaseDirectory() + "Shaders/" + shaderName + ".vsd";
		shaderID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::FragmentShader:
		filename = GetBaseDirectory() + "Shaders/" + shaderName + ".fsd";
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case ShaderType::GeometryShader:
		filename = GetBaseDirectory() + "Shaders/" + shaderName + ".gsd";
		shaderID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case ShaderType::ComputeShader:
		filename = GetBaseDirectory() + "Shaders/" + shaderName + ".csd";
		shaderID = glCreateShader(GL_COMPUTE_SHADER);
		break;
	}

	string shaderContent = LoadFileToString(filename);
	const char* shaderContentChar = shaderContent.c_str();
	
	glShaderSource(shaderID, 1, &shaderContentChar, nullptr);

	glCompileShader(shaderID);

	GLint getshader_success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &getshader_success);

	if (!getshader_success) 
	{
		GLchar infolog_vertex[1024];
		glGetShaderInfoLog(shaderID, sizeof(infolog_vertex), NULL, infolog_vertex);
		cout << "Error compiling shader: " << name << endl;
		fprintf(stderr, "%d: '%s'\n", GL_VERTEX_SHADER, infolog_vertex);
	}
}

Shader::~Shader()
{
	if (shaderID != 0)
	{
		glDeleteShader(shaderID);
	}
}