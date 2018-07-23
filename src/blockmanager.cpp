#include "blockmanager.h"
#include <cstring>
#include "texturemanager.h"

BlockManager::BlockManager()
{
	// register the air block to occupy the id 0
	BlockData airBlock{ 0, 0, 0 };
	blockData.push_back(airBlock);
}

int BlockManager::load(const char * fileTexSide, const char * fileTexTop, const char * fileTexBottom)
{
	BlockData bd;
	bd.texSide = TextureManager::load(fileTexSide);
	bd.texTop = bd.texBottom = bd.texSide;
	// if fileTexTop is nullptr, the top texture will be the same as the side texture
	if (fileTexTop)
		bd.texTop = TextureManager::load(fileTexTop);
	// if fileTexBottom is nullptr, the top texture will be the same as the top texture
	if (fileTexBottom)
		bd.texBottom = TextureManager::load(fileTexBottom);
	else
		bd.texBottom = bd.texTop;
	blockData.push_back(bd);
	return blockData.size() - 1;
}

const BlockData & BlockManager::getBlockData(int id) const
{
	return blockData[id];
}