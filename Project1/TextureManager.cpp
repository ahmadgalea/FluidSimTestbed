#include "TextureManager.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void TextureManager::LoadTextureFromFile(const string& name)
{
	Texture* texture = new Texture(name);
	textures.insert(pair<string, Texture*>(name, texture));
}

void TextureManager::LoadAllTextures()
{
	LoadTextureFromFile("blue_car");
}

void TextureManager::BindTextureFromName(const string& name, int textureUnit)
{
	//glUniform1i(location_list[texture_no], texture_no);
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	
	map<string, Texture*>::iterator textureIt = textures.find(name);
	
	if (textureIt != textures.end())
	{
		textureIt->second->Bind();
	}
	else
	{
		cout << "Error: Requested texture " << name << " not loaded." << endl;
	}
}