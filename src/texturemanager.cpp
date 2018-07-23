#include "texturemanager.h"
#include <algorithm>
#include <cstring>

std::vector<Texture> TextureManager::textures;
std::vector <std::string> TextureManager::filenames;

int TextureManager::load(const char * file)
{
	auto result = std::find(filenames.begin(), filenames.end(), file);
	if (result != filenames.end())
	{
		int index = result - filenames.begin();
		return index;
	}
	Texture t;
	char nameComplete[256];		// TODO: allocate memory dynamically
	strcpy_s(nameComplete, "textures/");
	strcat_s(nameComplete, file);
	t.load(nameComplete);
	textures.push_back(t);
	return textures.size() - 1;
}

Texture & TextureManager::get(int index)
{
	return textures[index];
}