#ifndef SELECTFRAME_H_
#define SELECTFRAME_H_

#include <glm/glm.hpp>
#include "cuberenderer.h"
#include "bidimensionalrenderer.h"
#include "world.h"
#include "player.h"

class SelectFrame
{
private:
	// pointers
	const Player * player;
	BidimensionalRenderer * bidRenderer;
	World * world;

	// selection
	double selPrecision;
	double selDistance;
	glm::ivec3 selBlock;
	// position of the adjacent block of the selected block,
	// i.e. the place to place a new block
	// if the right mouse button is down
	glm::ivec3 selBlockAdj;

	// textures
	int indexTexCursor;

	void select();

	// check if a component (X/Y/Z) has just go through an integer
	bool hasJustTraversedPositively(double frac) const { return frac < selPrecision; }
	bool hasJustTraversedNegatively(double frac) const { return frac > 1.0 - selPrecision; }
public:
	SelectFrame();
	void init(const Player * pPlayer, BidimensionalRenderer * pBidRenderer, World * pWorld);
	void update();
	void render() const;
	const glm::ivec3 & getSelBlock() const { return selBlock; }
	const glm::ivec3 & getSelBlockAdj() const { return selBlockAdj; }
};

#endif