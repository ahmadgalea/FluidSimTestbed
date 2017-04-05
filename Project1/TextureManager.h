#pragma once

#include "Texture.h"

#include <map>
#include <string>

using namespace std;

class TextureManager
{
private:
	map<string, Texture*> textures;
	GLuint noOfTextures = 0;
public:
	void LoadTextureFromFile(const string& name);
	void LoadAllTextures();
	Texture* GetTextureFromName(const string& name);
	void BindTextureFromName(const string& name);
};
