#ifndef RENDERBLOCK_H_
#define RENDERBLOCK_H_

#include "block.h"
#include "cuberenderer.h"

class RenderBlock
{
private:
	CubeRenderer * cubeRenderer;
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

	void init(CubeRenderer * pRenderer);

	void beginRender(long x, long y, long z, const Block * b, const glm::dvec3 & eyePosition, const glm::dvec3 & frontInScene, const glm::dvec3 & up);
	void render(int face);

	void clear();
};

#endif