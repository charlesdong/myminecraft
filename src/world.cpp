#include "world.h"
#include <iostream>

World::World()
{
}

void World::init()
{
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
			for (int k = 0; k < Z; k++)
			{
				if (j == 0)
					blocks[i][j][k] = new BlockBedrock;
				else if (j == 1 || j == 2)
					blocks[i][j][k] = new BlockStone;
				else if (j == 3)
					blocks[i][j][k] = new BlockDirt;
				else if (j == 4)
					blocks[i][j][k] = new BlockGrass;
			}
	renderer.init();
}

void World::render(const Camera & cam)
{
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
			for (int k = 0; k < Z; k++)
			{
				// NOTE: for OpenGL, the right-handed coordinate system is used
				renderer.beginRender(i, j, k, cam, blocks[i][j][k]);
				if (i == 0 || blocks[i - 1][j][k] == 0)
					renderer.render(LEFT);
				if (i == X - 1 || blocks[i + 1][j][k] == 0)
					renderer.render(RIGHT);
				if (j == 0 || blocks[i][j - 1][k] == 0)
					renderer.render(BOTTOM);
				if (j == Y - 1 || blocks[i][j + 1][k] == 0)
					renderer.render(TOP);
				if (k == 0 || blocks[i][j][k - 1] == 0)
					renderer.render(BACK);
				if (k == Z - 1 || blocks[i][j][k + 1] == 0)
					renderer.render(FRONT);
			}
}

void World::clear()
{
	renderer.clear();
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
			for (int k = 0; k < Z; k++)
				delete blocks[i][j][k];
}