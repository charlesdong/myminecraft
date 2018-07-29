#include "texturemanager.h"
#include <algorithm>
#include <cstring>

std::vector<Texture> TextureManager::textures;
std::vector <std::string> TextureManager::filenames;

int TextureManager::load(const char * filename)
{
	// get the complete file name
	char filenameComplete[256];		// TODO: allocate memory dynamically
	strcpy_s(filenameComplete, "textures/");
	strcat_s(filenameComplete, filename);

	// check if texture under the same name has loaded
	auto result = std::find(filenames.begin(), filenames.end(), filename);
	if (result != filenames.end())
	{
		int index = result - filenames.begin();
		return index;
	}

	filenames.push_back(filename);
	Texture t;
	t.load(filenameComplete);
	textures.push_back(t);

	return textures.size() - 1;
}

Texture & TextureManager::get(int index)
{
	return textures[index];
}