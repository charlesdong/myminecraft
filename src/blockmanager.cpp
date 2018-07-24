#include "blockmanager.h"
#include <cstring>
#include "texturemanager.h"

BlockManager::BlockManager()
{
	// register the air block to occupy the id 0
	BlockData airBlock{ "", "", "" };
	blockData.push_back(airBlock);
}

int BlockManager::load(const char * texSide, const char * texTop, const char * texBottom)
{
	BlockData bd;
	bd.texSide = texSide;
	TextureManager::load(texSide);
	bd.texTop = bd.texBottom = bd.texSide;
	// if fileTexTop is nullptr, the top texture will be the same as the side texture
	if (texTop)
	{
		bd.texTop = texTop;
		TextureManager::load(texTop);
	}
	// if fileTexBottom is nullptr, the top texture will be the same as the top texture
	if (texBottom)
	{
		bd.texBottom = texBottom;
		TextureManager::load(texBottom);
	}
	else
		bd.texBottom = bd.texTop;
	blockData.push_back(bd);
	return blockData.size() - 1;
}

const BlockData & BlockManager::getBlockData(int id) const
{
	return blockData[id];
}