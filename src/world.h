#ifndef WORLD_H_
#define WORLD_H_

#include "block.h"
#include "aabb.h"
#include <vector>

class World
{
public:
	static const int WORLD_X = 10;
	static const int WORLD_Y = 10;
	static const int WORLD_Z = 10;

private:
	Block * blocks[WORLD_X][WORLD_X][WORLD_X];
	//RenderBlock renderer;

public:
	World();
	void init();
	//void render();
	void clear();

	bool inRange(long x, long y, long z) const;
	bool hasBlock(long x, long y, long z) const;
	bool hasBlockSimple(long x, long y, long z) const;
	const Block * getBlockPtr(long x, long y, long z) const;
	void destroyBlock(long x, long y, long z);
	void setBlock(long x, long y, long z);
	std::vector<AABB> getHitboxes(const AABB & box);
};

#endif