#include "renderblock.h"
#include "texturemanager.h"

RenderBlock::RenderBlock()
{
}

void RenderBlock::init(CubeRenderer * pCubeRenderer)
{
	loadTextures();
	cubeRenderer = pCubeRenderer;
}

void RenderBlock::loadTextures()
{
	idDirt = blockMgr.load("block/dirt.png");
	idGrass = blockMgr.load("block/grass_side.png", "block/grass_top.png", "block/dirt.png");
	idStone = blockMgr.load("block/stone.png");
	idBedrock = blockMgr.load("block/bedrock.png");
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

void RenderBlock::beginRender(
	long x,
	long y,
	long z,
	const Block * b,
	const glm::dvec3 & eyePosition,
	const glm::dvec3 & frontInScene,
	const glm::dvec3 & up
)
{
	cubeRenderer->beginRender(x, y, z, eyePosition, frontInScene, up);
	idCurrent = getBlockType(b);
}

void RenderBlock::render(int face) const
{
	cubeRenderer->setAuxColor(glm::vec3(1.0f, 1.0f, 1.0f));
	if (face == TOP)
	{
		if (idCurrent == idGrass)
			cubeRenderer->setAuxColor(glm::vec3(0.71f, 1.18f, 0.34f));
		TextureManager::get(blockMgr.getBlockData(idCurrent).texTop).bind();
	}
	else if (face == BOTTOM)
		TextureManager::get(blockMgr.getBlockData(idCurrent).texBottom).bind();
	else
		TextureManager::get(blockMgr.getBlockData(idCurrent).texSide).bind();
	cubeRenderer->render(face);
}

void RenderBlock::clear()
{
	cubeRenderer->clear();
}