#ifndef WORLD_H_
#define WORLD_H_

#include "renderblock.h"
#include "block.h"

class World
{
private:
	static const int X = 10;
	static const int Y = 5;
	static const int Z = 10;

	Block * blocks[X][Y][Z];
	RenderBlock renderer;
public:
	World();
	void init();
	void render(const Camera & cam);
	void clear();
};

#endif