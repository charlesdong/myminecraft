#include "world.h"

World::World()
{
}

void World::init()
{
	// TODO: magic numbers
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
			for (int k = 0; k < Z; k++)
			{
				if (j == 0)
					blocks[i][j][k] = 1;	// TODO: MN (for dirt)
				else if (j == 1)
					blocks[i][j][k] = 2;	// TODO: MN (for grass)
			}
	renderer.init();
}

void World::render(const Camera & cam) const
{
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
			for (int k = 0; k < Z; k++)
				renderer.render(i, j, k, cam, blocks[i][j][k]);
}

void World::clear()
{
	renderer.clear();
}