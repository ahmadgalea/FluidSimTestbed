#include "ShaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader) : vertexShader(vertexShader), fragmentShader(fragmentShader)
{
	programName = vertexShader->name + fragmentShader->name;

	glAttachShader(programID, vertexShader->shaderID);
	glAttachShader(programID, fragmentShader->shaderID);

	LinkProgram();

	glValidateProgram(programID);

	glDetachShader(programID, vertexShader->shaderID);
	glDetachShader(programID, fragmentShader->shaderID);
}

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader, Shader* geometryShader) : vertexShader(vertexShader), fragmentShader(fragmentShader), geometryShader(geometryShader)
{
	programName = vertexShader->name + fragmentShader->name + geometryShader->name;

	glAttachShader(programID, vertexShader->shaderID);
	glAttachShader(programID, fragmentShader->shaderID);
	glAttachShader(programID, geometryShader->shaderID);

	glValidateProgram(programID);

	LinkProgram();

	glDetachShader(programID, vertexShader->shaderID);
	glDetachShader(programID, fragmentShader->shaderID);
	glDetachShader(programID, geometryShader->shaderID);
}

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader, Shader* geometryShader, Shader* computeShader) : vertexShader(vertexShader), fragmentShader(fragmentShader), geometryShader(geometryShader), computeShader(computeShader)
{
	programName = vertexShader->name + fragmentShader->name + geometryShader->name + computeShader->name;

	glAttachShader(programID, vertexShader->shaderID);
	glAttachShader(programID, fragmentShader->shaderID);
	glAttachShader(programID, geometryShader->shaderID);
	glAttachShader(programID, computeShader->shaderID);

	glValidateProgram(programID);

	LinkProgram();

	glDetachShader(programID, vertexShader->shaderID);
	glDetachShader(programID, fragmentShader->shaderID);
	glDetachShader(programID, geometryShader->shaderID);
	glDetachShader(programID, computeShader->shaderID);
}

void ShaderProgram::LinkProgram()
{
	glLinkProgram(programID);

	GLint linkshader_success;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkshader_success);

	if (linkshader_success == 0) {
		GLchar ErrorLog[1024];
		glGetProgramInfoLog(programID, sizeof(ErrorLog), NULL, ErrorLog);
		cout << "Error linking shader program: " << programName << endl;
		fprintf(stderr, "'%s'\n", ErrorLog);
	};

}

void ShaderProgram::Bind()
{
	glUseProgram(programID);
}

GLint ShaderProgram::GetAttributeLocation(const string& name) const
{
	return glGetAttribLocation(programID, name.c_str());
}

ShaderProgram::~ShaderProgram()
{
	GLenum ErrorCheckValue = glGetError();

	glUseProgram(0);
	glDeleteProgram(programID);

	if (ErrorCheckValue != GL_NO_ERROR) {
		cout << "Error deleting shader program: " <<programName<< endl;
	};
}
