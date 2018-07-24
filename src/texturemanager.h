#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

//#include <vector>
#include <string>
#include <map>
#include "texture.h"

class TextureManager
{
private:
	//static std::vector<Texture> textures;
	//static std::vector<std::string> filenames;
	static std::map<std::string, Texture> textures;
public:
	static void load(const char * name);
	static Texture & get(const char * name);
};

#endif