#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <GL/glew.h>

#include <cstdio>
#include "game.h"

Texture::Texture()
{
}

void Texture::load(const char * path)
{
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	// NOTE: for transparent textures, GL_CLAMP_TO_EDGE is better
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// NOTE: for pixel-styled textures (that's MC's texture style!), GL_NEAREST should be used
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height;
	stbi_set_flip_vertically_on_load(true);		// flip the texture vertically
	unsigned char * image = stbi_load(path, &width, &height, nullptr, 4);
	if (!image)
	{
		char log[256];
		sprintf_s(log, "Failed to load image from file %s (maybe doesn't exist)", path);
		pGame->getLogger().log(ERROR, log);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, tex);
}

void Texture::clear()
{
	glDeleteTextures(1, &tex);
}