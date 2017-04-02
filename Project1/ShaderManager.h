#pragma once

#include "ShaderProgram.h"
#include "Shader.h"

#include <string>
#include <map>

using namespace std;

class ShaderManager
{
private:
	map<string, Shader*> fragmentShaders;
	map<string, Shader*> vertexShaders;
	map<string, Shader*> geometryShaders;
	map<string, Shader*> computeShaders;
	map<string, ShaderProgram*> shaderPrograms;
public:
	ShaderManager() {}
	~ShaderManager();

	void LoadVertexShader(const string& name);
	void LoadFragmentShader(const string& name);
	void LoadGeometryShader(const string& name);
	void LoadComputeShader(const string& name);

	bool LoadShaderProgram(const string& vertexName, const string& fragmentName);
	bool LoadShaderProgram(const string& vertexName, const string& fragmentName, const string& geometryName);
	bool LoadShaderProgram(const string& vertexName, const string& fragmentName, const string& geometryName, const string& computeName);

	void LoadAllShaders();

	ShaderProgram* GetProgramFromName(const string& programName);
	void BindProgramFromName(const string& programName);

};