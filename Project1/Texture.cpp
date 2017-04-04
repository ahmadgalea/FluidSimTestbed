#include "Texture.h"
#include "GlobalIOUtilities.h"

#include "SOIL.h"

Texture::Texture(const string& name, GLenum imageFormat)
{
	string filename = GetBaseDirectory() + "Textures/" + name + ".png";
	pixelData = SOIL_load_image(filename.c_str(), &width, &height, 0, imageFormat);

	glGenTextures(1, &textureID);

	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	if (glIsTexture(textureID) != GL_TRUE)
	{
		std::cout << "Error creating texture: " << name << std::endl;
	}
}

Texture::~Texture()
{
	SOIL_free_image_data(pixelData);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}