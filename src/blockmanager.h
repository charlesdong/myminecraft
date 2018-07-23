#ifndef BLOCKMANAGER_H_
#define BLOCKMANAGER_H_

#include <vector>
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
	int load(const char * fileTexSide, const char * fileTexTop = nullptr, const char * fileTexBottom = nullptr);
	const BlockData & getBlockData(int id) const;
};

#endif