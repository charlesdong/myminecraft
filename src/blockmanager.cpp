#include "blockmanager.h"
#include <cstring>
#include "texturemanager.h"

BlockManager::BlockManager()
{
}

int BlockManager::load(const char * texSide, const char * texTop, const char * texBottom)
{
	BlockData bd;
	bd.texSide = TextureManager::load(texSide);
	bd.texTop = bd.texBottom = bd.texSide;
	// if fileTexTop is nullptr, the top texture will be the same as the side texture
	if (texTop)
		bd.texTop = TextureManager::load(texTop);
	// if fileTexBottom is nullptr, the top texture will be the same as the top texture
	if (texBottom)
		bd.texBottom = TextureManager::load(texBottom);
	else
		bd.texBottom = bd.texTop;
	blockData.push_back(bd);
	return blockData.size() - 1;
}

const BlockData & BlockManager::getBlockData(int id) const
{
	return blockData[id];
}