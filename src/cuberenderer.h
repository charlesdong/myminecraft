#ifndef CUBERENDERER_H_
#define CUBERENDERER_H_

#include <vector>

#include "camera.h"
#include "program.h"
#include "texture.h"
#include "blockmanager.h"

enum Face { BACK, FRONT, LEFT, RIGHT, BOTTOM, TOP };

class CubeRenderer
{
private:
	unsigned int vao;
	unsigned int vbo;
	Program prog;
	BlockManager blockMgr;
	int blockId;

	BlockData bd;

	void loadTextures();
public:
	CubeRenderer();
	void init();
	void beginRender(long x, long y, long z, const Camera & cam, int bId);
	void render(int face) const;
	void clear();
};

#endif