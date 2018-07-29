#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <vector>
#include <string>
#include <map>
#include "texture.h"

class TextureManager
{
private:
	static std::vector<Texture> textures;
	static std::vector<std::string> filenames;
public:
	static int load(const char * filename);
	static Texture & get(int index);
};

#endif