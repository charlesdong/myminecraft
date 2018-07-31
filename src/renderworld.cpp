#include "renderworld.h"

void RenderWorld::init(World * pWorld, RenderBlock * pRenderBlock)
{
	world = pWorld;
	renderBlock = pRenderBlock;
}

void RenderWorld::render()
{
	/*
	for (int i = 0; i < X; i++)
	for (int j = 0; j < Y; j++)
	for (int k = 0; k < Z; k++)
	{
	// do not render empty/air blocks
	if (blocks[i][j][k] == nullptr)
	continue;

	// NOTE: for OpenGL, the right-handed coordinate system is used
	renderer.beginRender(i, j, k, blocks[i][j][k]);
	if (i == 0 || blocks[i - 1][j][k] == nullptr)
	renderer.render(LEFT);
	if (i == X - 1 || blocks[i + 1][j][k] == nullptr)
	renderer.render(RIGHT);
	if (j == 0 || blocks[i][j - 1][k] == nullptr)
	renderer.render(BOTTOM);
	if (j == Y - 1 || blocks[i][j + 1][k] == nullptr)
	renderer.render(TOP);
	if (k == 0 || blocks[i][j][k - 1] == nullptr)
	renderer.render(BACK);
	if (k == Z - 1 || blocks[i][j][k + 1] == nullptr)
	renderer.render(FRONT);
	*/
	for (int x = 0; x < World::WORLD_X; x++)
		for (int y = 0; y < World::WORLD_Y; y++)
			for (int z = 0; z < World::WORLD_Z; z++)
			{
				if (!world->hasBlockSimple(x, y, z))
					continue;

				renderBlock->beginRender(x, y, z, world->getBlockPtr(x, y, z));
				if (x == 0 || !world->hasBlockSimple(x - 1, y, z))
					renderBlock->render(LEFT);
				if (x == World::WORLD_X - 1 || !world->hasBlockSimple(x + 1, y, z))
					renderBlock->render(RIGHT);
				if (y == 0 || !world->hasBlockSimple(x, y - 1, z))
					renderBlock->render(BOTTOM);
				if (y == World::WORLD_Y - 1 || !world->hasBlockSimple(x, y + 1, z))
					renderBlock->render(TOP);
				if (z == 0 || !world->hasBlockSimple(x, y, z - 1))
					renderBlock->render(BACK);
				if (z == World::WORLD_Z - 1 || !world->hasBlockSimple(x, y, z + 1))
					renderBlock->render(FRONT);
			}
}