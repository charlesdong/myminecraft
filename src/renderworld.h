#ifndef RENDERWORLD_H_
#define RENDERWORLD_H_

#include "world.h"
#include "renderblock.h"

class RenderWorld
{
private:
	World * world;
	RenderBlock * renderBlock;
public:
	void init(World * pWorld, RenderBlock * pRenderBlock);
	void render();
};

#endif