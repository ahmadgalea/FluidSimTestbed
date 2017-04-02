#include "ShaderManager.h"

#include <iostream>

void ShaderManager::LoadVertexShader(const string& name)
{
	Shader* vertexShader = new Shader(ShaderType::VertexShader, name);
	vertexShaders.insert(pair<string, Shader*>(name, vertexShader));
}

void ShaderManager::LoadFragmentShader(const string& name)
{
	Shader* fragmentShader = new Shader(ShaderType::FragmentShader, name);
	fragmentShaders.insert(pair<string, Shader*>(name, fragmentShader));
}

void ShaderManager::LoadGeometryShader(const string& name)
{
	Shader* geometryShader = new Shader(ShaderType::GeometryShader, name);
	geometryShaders.insert(pair<string, Shader*>(name, geometryShader));
}

void ShaderManager::LoadComputeShader(const string& name)
{
	Shader* computeShader = new Shader(ShaderType::ComputeShader, name);
	computeShaders.insert(pair<string, Shader*>(name, computeShader));
}

bool ShaderManager::LoadShaderProgram(const string& vertexName, const string& fragmentName)
{
	if (!vertexShaders.at(vertexName))
	{
		cout << "Attempted to link shader between \"" << vertexName << "\" and \"" << fragmentName << "\" but vertex shader not loaded." << endl;
		return false;
	}
	if (!fragmentShaders.at(fragmentName))
	{
		cout << "Attempted to link shader between \"" << vertexName << "\" and \"" << fragmentName << "\" but fragment shader not loaded." << endl;
		return false;
	}

	ShaderProgram* shaderProgram = new ShaderProgram(vertexShaders.at(vertexName), fragmentShaders.at(fragmentName));
	shaderPrograms.insert(pair<string, ShaderProgram*>(shaderProgram->programName, shaderProgram));

}

bool ShaderManager::LoadShaderProgram(const string& vertexName, const string& fragmentName, const string& geometryName)
{
	if (!vertexShaders.at(vertexName))
	{
		cout << "Attempted to link shader between \"" << vertexName << "\" , \"" << fragmentName << "\" and \"" << geometryName << "\" but vertex shader not loaded." << endl;
		return false;
	}
	if (!fragmentShaders.at(fragmentName))
	{
		cout << "Attempted to link shader between \"" << vertexName << "\" , \"" << fragmentName << "\" and \"" << geometryName << "\" but fragment shader not loaded." << endl;
		return false;
	}
	if (!geometryShaders.at(geometryName))
	{
		cout << "Attempted to link shader between \"" << vertexName << "\" , \"" << fragmentName << "\" and \"" << geometryName << "\" but geometry shader not loaded." << endl;
		return false;
	}

	ShaderProgram* shaderProgram = new ShaderProgram(vertexShaders.at(vertexName), fragmentShaders.at(fragmentName), geometryShaders.at(geometryName));
	shaderPrograms.insert(pair<string, ShaderProgram*>(shaderProgram->programName, shaderProgram));
}

bool ShaderManager::LoadShaderProgram(const string& vertexName, const string& fragmentName, const string& geometryName, const string& computeName)
{
	if (!vertexShaders.at(vertexName))
	{
		cout << "Attempted to link shader between \"" << vertexName << "\" , \"" << fragmentName << "\" , \"" << geometryName << "\" and \"" << computeName << "\" but vertex shader not loaded." << endl;
		return false;
	}
	if (!fragmentShaders.at(fragmentName))
	{
		cout << "Attempted to link shader between \"" << vertexName << "\" , \"" << fragmentName << "\" , \"" << geometryName << "\" and \"" << computeName << "\" but fragment shader not loaded." << endl;
		return false;
	}
	if (!geometryShaders.at(geometryName))
	{
		cout << "Attempted to link shader between \"" << vertexName << "\" , \"" << fragmentName << "\" , \"" << geometryName << "\" and \"" << computeName << "\" but geometry shader not loaded." << endl;
		return false;
	}
	if (!computeShaders.at(computeName))
	{
		cout << "Attempted to link shader between \"" << vertexName << "\" , \"" << fragmentName << "\" , \"" << geometryName << "\" and \"" << computeName << "\" but compute shader not loaded." << endl;
		return false;
	}

	ShaderProgram* shaderProgram = new ShaderProgram(vertexShaders.at(vertexName), fragmentShaders.at(fragmentName), geometryShaders.at(geometryName), computeShaders.at(computeName));
	shaderPrograms.insert(pair<string, ShaderProgram*>(shaderProgram->programName, shaderProgram));
}

void ShaderManager::LoadAllShaders()
{
	LoadVertexShader("SimpleVertex");
	LoadFragmentShader("SimpleFragment");

	LoadShaderProgram("SimpleVertex", "SimpleFragment");
}

ShaderProgram* ShaderManager::GetProgramFromName(const string& programName)
{
	map<string, ShaderProgram*>::iterator programIterator = shaderPrograms.find(programName);
	if (programIterator != shaderPrograms.end())
	{
		return programIterator->second;
	}
	else
	{
		cout << "Error: Shader program " << programName << " not found in list of compiled programs." << endl;
		return nullptr;
	}
}

void ShaderManager::BindProgramFromName(const string& programName)
{
	map<string, ShaderProgram*>::iterator programIterator = shaderPrograms.find(programName);
	if (programIterator != shaderPrograms.end())
	{
		programIterator->second->Bind();
	}
	else
	{
		cout << "Error: Shader program " << programName << " not found in list of compiled programs." << endl;
	}
}

ShaderManager::~ShaderManager()
{
	for (auto vertexShader : vertexShaders)
	{
		delete vertexShader.second;
	}
	for (auto fragmentShader :fragmentShaders)
	{
		delete fragmentShader.second;
	}
	for (auto geometryShader : geometryShaders)
	{
		delete geometryShader.second;
	}
	for (auto computeShader : computeShaders)
	{
		delete computeShader.second;
	}
	for (auto shaderProgram : shaderPrograms)
	{
		delete shaderProgram.second;
	}
}