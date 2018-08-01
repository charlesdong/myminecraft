#include "world.h"
#include <glm/glm.hpp>

World::World()
{
}

void World::init(RenderBlock * pRenderBlock)
{
	for (int i = 0; i < WORLD_X; i++)
		for (int j = 0; j < WORLD_Y; j++)
			for (int k = 0; k < WORLD_Z; k++)
			{
				if (j == 0)
					blocks[i][j][k] = new BlockBedrock;
				else if (j == 1 || j == 2)
					blocks[i][j][k] = new BlockStone;
				else if (j == 3)
					blocks[i][j][k] = new BlockDirt;
				else if (j == 4)
					blocks[i][j][k] = new BlockGrass;
				else
					blocks[i][j][k] = nullptr;
			}
	renderBlock = pRenderBlock;
}

void World::render(const glm::dvec3 & eyePosition, const glm::dvec3 & frontInScene, const glm::dvec3 & up) const
{
	for (int i = 0; i < WORLD_X; i++)
		for (int j = 0; j < WORLD_Y; j++)
			for (int k = 0; k < WORLD_Z; k++)
			{
				// do not render empty/air blocks
				if (blocks[i][j][k] == nullptr)
					continue;

				// NOTE: for OpenGL, the right-handed coordinate system is used
				renderBlock->beginRender(i, j, k, blocks[i][j][k], eyePosition, frontInScene, up);
				if (i == 0 || blocks[i - 1][j][k] == nullptr)
					renderBlock->render(LEFT);
				if (i == WORLD_X - 1 || blocks[i + 1][j][k] == nullptr)
					renderBlock->render(RIGHT);
				if (j == 0 || blocks[i][j - 1][k] == nullptr)
					renderBlock->render(BOTTOM);
				if (j == WORLD_Y - 1 || blocks[i][j + 1][k] == nullptr)
					renderBlock->render(TOP);
				if (k == 0 || blocks[i][j][k - 1] == nullptr)
					renderBlock->render(BACK);
				if (k == WORLD_Z - 1 || blocks[i][j][k + 1] == nullptr)
					renderBlock->render(FRONT);
			}
}

void World::clear()
{
	renderBlock->clear();
	for (int i = 0; i < WORLD_X; i++)
		for (int j = 0; j < WORLD_Y; j++)
			for (int k = 0; k < WORLD_Z; k++)
				delete blocks[i][j][k];
}

bool World::inRange(long x, long y, long z) const
{
	return x >= 0L && x < WORLD_X && y >= 0L && y < WORLD_Y && z >= 0L && z < WORLD_Z;
}

bool World::hasBlock(long x, long y, long z) const
{
	return inRange(x, y, z) && blocks[x][y][z] != nullptr;
}

bool World::hasBlockSimple(long x, long y, long z) const
{
	return blocks[x][y][z] != nullptr;
}

const Block * World::getBlockPtr(long x, long y, long z) const
{
	// TODO: Range checking.
	return blocks[x][y][z];
}
void World::destroyBlock(long x, long y, long z)
{
	if (inRange(x, y, z))
	{
		delete blocks[x][y][z];
		blocks[x][y][z] = nullptr;
	}
}

void World::setBlock(long x, long y, long z)
{
	if (inRange(x, y, z))
	{
		delete blocks[x][y][z];
		blocks[x][y][z] = new BlockStone;
	}
}

std::vector<AABB> World::getHitboxes(const AABB & box) const
{
	std::vector<AABB> hitboxes;
	// NOTE: The range of every component should be floor(min)~floor(max),
	// due to all 3 component of a block's position are smallest.
	for (double x = floor(box.xmin); x <= floor(box.xmax); x += 1.0)
		for (double y = floor(box.ymin); y <= floor(box.ymax); y += 1.0)
			for (double z = floor(box.zmin); z <= floor(box.zmax); z += 1.0)
				if (hasBlock((long)x, (long)y, (long)z))
					hitboxes.push_back(AABB(x, x + 1.0, y, y + 1.0, z, z + 1.0));
	return hitboxes;
}