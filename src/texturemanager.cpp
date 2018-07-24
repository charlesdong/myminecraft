#include "texturemanager.h"
#include <algorithm>
#include <cstring>

//std::vector<Texture> TextureManager::textures;
//std::vector <std::string> TextureManager::filenames;
std::map<std::string, Texture> TextureManager::textures;

void TextureManager::load(const char * name)
{
	/*
	auto result = std::find(filenames.begin(), filenames.end(), file);
	if (result != filenames.end())
	{
		int index = result - filenames.begin();
		return index;
	}
	*/
	if (textures.find(name) != textures.end())
		return;

	Texture t;
	char filename[256];		// TODO: allocate memory dynamically
	strcpy_s(filename, "textures/");
	strcat_s(filename, name);
	strcat_s(filename, ".png");
	t.load(filename);
	//textures.push_back(t);
	textures[name] = t;
}

Texture & TextureManager::get(const char * name)
{
	return textures[name];
}