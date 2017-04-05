#include "TextureManager.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void TextureManager::LoadTextureFromFile(const string& name)
{
	Texture* texture = new Texture(name);
	texture->textureUnit = noOfTextures;

	textures.insert(pair<string, Texture*>(name, texture));
	noOfTextures++;
}

void TextureManager::LoadAllTextures()
{
	LoadTextureFromFile("blue_car");
}

Texture* TextureManager::GetTextureFromName(const string& name)
{
	map<string, Texture*>::iterator textureIt = textures.find(name);

	if (textureIt != textures.end())
	{
		return textureIt->second;
	}
	else
	{
		cout << "Error: Requested texture " << name << " not loaded." << endl;
		return nullptr;
	}
}

void TextureManager::BindTextureFromName(const string& name)
{
	//glUniform1i(location_list[texture_no], texture_no);
	
	
	map<string, Texture*>::iterator textureIt = textures.find(name);
	
	if (textureIt != textures.end())
	{
		glActiveTexture(GL_TEXTURE0 + textureIt->second->textureUnit);
		textureIt->second->Bind();
	}
	else
	{
		cout << "Error: Requested texture " << name << " not loaded." << endl;
	}
}