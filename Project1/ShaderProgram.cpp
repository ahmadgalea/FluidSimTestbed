#include "ShaderProgram.h"

#include <iostream>

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader) : vertexShader(vertexShader), fragmentShader(fragmentShader)
{
	programName = vertexShader->name + fragmentShader->name;

	programID = glCreateProgram();

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

	programID = glCreateProgram();

	glAttachShader(programID, vertexShader->shaderID);
	glAttachShader(programID, fragmentShader->shaderID);
	glAttachShader(programID, geometryShader->shaderID);

	LinkProgram();

	glValidateProgram(programID);

	glDetachShader(programID, vertexShader->shaderID);
	glDetachShader(programID, fragmentShader->shaderID);
	glDetachShader(programID, geometryShader->shaderID);
}

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader, Shader* geometryShader, Shader* computeShader) : vertexShader(vertexShader), fragmentShader(fragmentShader), geometryShader(geometryShader), computeShader(computeShader)
{
	programName = vertexShader->name + fragmentShader->name + geometryShader->name + computeShader->name;

	programID = glCreateProgram();

	glAttachShader(programID, vertexShader->shaderID);
	glAttachShader(programID, fragmentShader->shaderID);
	glAttachShader(programID, geometryShader->shaderID);
	glAttachShader(programID, computeShader->shaderID);

	LinkProgram();

	glValidateProgram(programID);

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

GLint ShaderProgram::GetUniformLocation(const string& name) const
{
	return glGetUniformLocation(programID, name.c_str());
}

bool ShaderProgram::SetVertexAttribute(const string& name, int size)
{
	GLenum ErrorCheckValue = glGetError();

	int attribIndex = GetAttributeLocation(name);

	glVertexAttribPointer(attribIndex, size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribIndex);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		cout << "ERROR: Could not assign attribute " << name << endl;
		fprintf(stderr, "%s \n", gluErrorString(ErrorCheckValue));
		return false;
	}

	return true;
}

bool ShaderProgram::SetMat4FUniform(const string& name, const mat4* matrixPointer)
{
	GLenum ErrorCheckValue = glGetError();

	int uniformLocation = GetUniformLocation(name);
	
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value_ptr(*(mat4*)matrixPointer));

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		cout << "ERROR: Could not assign uniform " << name << endl;
		fprintf(stderr, "%s \n", gluErrorString(ErrorCheckValue));
		return false;
	}

	return true;
}

bool ShaderProgram::SetScalIUniform(const string& name, int uniformValue)
{
	GLenum ErrorCheckValue = glGetError();

	int uniformLocation = GetUniformLocation(name);

	glUniform1i(uniformLocation, uniformValue);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		cout << "ERROR: Could not assign uniform " << name << endl;
		fprintf(stderr, "%s \n", gluErrorString(ErrorCheckValue));
		return false;
	}

	return true;
}

void ShaderProgram::AddShaderMatrix(const string& name, const mat4* matrixPointer)
{
	matrixPointers.insert(pair<string, mat4*>(name, (mat4*)matrixPointer));
}

void ShaderProgram::AddTexture(const string& name, Texture*texturePointer)
{
	texturePointers.insert(pair<string, Texture*>(name, texturePointer));
	texturePointer->Bind();
	UpdateShaderTextures();
}

void ShaderProgram::UpdateShaderMatrices()
{
	Bind();

	for (pair<string, mat4*> pointer : matrixPointers)
	{
		SetMat4FUniform(pointer.first, pointer.second);
	}
}

void ShaderProgram::UpdateShaderTextures()
{
	Bind();

	for (pair<string, Texture*> pointer : texturePointers)
	{
		SetScalIUniform(pointer.first, pointer.second->textureUnit);
	}
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
