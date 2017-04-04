#pragma once

#include "Texture.h"

#include <map>
#include <string>

using namespace std;

class TextureManager
{
private:
	map<string, Texture*> textures;
public:
	void LoadTextureFromFile(const string& name);
	void LoadAllTextures();
	void BindTextureFromName(const string& name, int textureUnit = 0);
};
