#ifndef RENDERBLOCK_H_
#define RENDERBLOCK_H_

#include "camera.h"
#include "block.h"
#include "cuberenderer.h"

class RenderBlock
{
private:
	CubeRenderer renderer;
	BlockManager blockMgr;
	short idCurrent;

	short idDirt;
	short idGrass;
	short idStone;
	short idBedrock;

	void loadTextures();
	short getBlockType(const Block * b) const;
public:
	RenderBlock();

	void init();

	void beginRender(long x, long y, long z, const Camera & cam, const Block * b);
	void render(int face);

	void clear();
};

#endif