#ifndef CUBERENDERER_H_
#define CUBERENDERER_H_

#include <vector>

#include "camera.h"
#include "program.h"
#include "texture.h"

class CubeRenderer
{
private:
	unsigned int vao;
	unsigned int vbo;
	int tex;
	Program prog;
	std::vector<Texture> textures;

	void loadTextures();
	int loadTexture(const char * path);
public:
	CubeRenderer();
	void init();
	void render(long x, long y, long z, const Camera & cam, int blockId) const;
	void clear();
};

#endif