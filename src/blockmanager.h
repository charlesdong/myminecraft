#ifndef BLOCKMANAGER_H_
#define BLOCKMANAGER_H_

#include <vector>
#include <string>
#include "texture.h"

struct BlockData
{
	int texTop;
	int texBottom;
	int texSide;
};

class BlockManager
{
private:
	std::vector<BlockData> blockData;
public:
	BlockManager();
	int load(const char * texSide, const char * texTop = nullptr, const char * texBottom = nullptr);
	const BlockData & getBlockData(int id) const;
};

#endif