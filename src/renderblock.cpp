#include "renderblock.h"
#include "texturemanager.h"

RenderBlock::RenderBlock()
{
}

void RenderBlock::init(CubeRenderer * pRenderer)
{
	renderer = pRenderer;
	loadTextures();
}

void RenderBlock::loadTextures()
{
	idDirt = blockMgr.load("dirt");
	idGrass = blockMgr.load("grass_side", "grass_top", "dirt");
	idStone = blockMgr.load("stone");
	idBedrock = blockMgr.load("bedrock");
}

short RenderBlock::getBlockType(const Block * b) const
{
	if (typeid(*b) == typeid(BlockDirt))
		return idDirt;
	if (typeid(*b) == typeid(BlockGrass))
		return idGrass;
	if (typeid(*b) == typeid(BlockStone))
		return idStone;
	if (typeid(*b) == typeid(BlockBedrock))
		return idBedrock;
}

void RenderBlock::beginRender(long x, long y, long z, const Camera & cam, const Block * b)
{
	renderer->beginRender(x, y, z, cam);
	idCurrent = getBlockType(b);
}

void RenderBlock::render(int face)
{
	renderer->setAuxColor(glm::vec3(1.0f, 1.0f, 1.0f));
	if (face == TOP)
	{
		if (idCurrent == idGrass)
			renderer->setAuxColor(glm::vec3(0.71f, 1.18f, 0.34f));
		TextureManager::get(blockMgr.getBlockData(idCurrent).texTop).bind();
	}
	else if (face == BOTTOM)
		TextureManager::get(blockMgr.getBlockData(idCurrent).texBottom).bind();
	else
		TextureManager::get(blockMgr.getBlockData(idCurrent).texSide).bind();
	renderer->render(face);
}

void RenderBlock::clear()
{
	renderer->clear();
}