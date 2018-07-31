#ifndef WORLD_H_
#define WORLD_H_

#include "block.h"
#include "aabb.h"
#include "renderblock.h"
#include "cuberenderer.h"
#include <vector>

class World
{
public:
	static const int WORLD_X = 10;
	static const int WORLD_Y = 10;
	static const int WORLD_Z = 10;

private:
	Block * blocks[WORLD_X][WORLD_X][WORLD_X];
	RenderBlock * renderBlock;

public:
	World();
	void init(RenderBlock * pRenderBlock);
	void render(const glm::dvec3 & eyePosition, const glm::dvec3 & frontInScene, const glm::dvec3 & up);
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