#include "selectframe.h"
#include "texturemanager.h"
#include "game.h"
#include "aabb.h"
#include <iostream>

SelectFrame::SelectFrame()
{
	player = nullptr;
}

void SelectFrame::init(const Player * pPlayer, BidimensionalRenderer * pBidRenderer, World * pWorld)
{
	player = pPlayer;
	bidRenderer = pBidRenderer;
	world = pWorld;
	selPrecision = 0.025;
	selDistance = 4.0;

	indexTexCursor = TextureManager::load("gui/cursor.png");
}

void SelectFrame::update()
{
	select();
	static bool buttonLeft = false;
	static bool buttonRight = false;
	if (selBlock.x != -1 || selBlock.y != -1 || selBlock.z != -1)
	{
		if (pGame->isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
		{
			if (!buttonLeft)
			{
				world->destroyBlock(selBlock.x, selBlock.y, selBlock.z);
				buttonLeft = true;
			}
		}
		else
			buttonLeft = false;
		if (pGame->isMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
		{
			if (!buttonRight)
			{
				if (!collide(player->getHitbox(), AABB((double)selBlockAdj.x, (double)selBlockAdj.x + 1.0, (double)selBlockAdj.y, (double)selBlockAdj.y + 1.0, (double)selBlockAdj.z, (double)selBlockAdj.z + 1.0)))
					world->setBlock(selBlockAdj.x, selBlockAdj.y, selBlockAdj.z);
				buttonRight = true;
			}
		}
		else
			buttonRight = false;
	}
}

void SelectFrame::select()
{
	glm::dvec3 posCur = player->getEyePosition();
	glm::ivec3 result(-1, -1, -1);				// Currently, a position of (-1, -1, -1) means "none selected"
	// selecting principle: emit a ray from the eye towards the front
	// and extend it continuously (until limit reached), see what's
	// the first block it go through
	for (double dist = selPrecision; dist <= selDistance; dist += selPrecision)
	{
		posCur += player->getFrontInScene() * selPrecision;
		result.x = (int)floor(posCur.x);
		result.y = (int)floor(posCur.y);
		result.z = (int)floor(posCur.z);
		if (world->hasBlock(result.x, result.y, result.z))
		{
			selBlock.x = result.x;
			selBlock.y = result.y;
			selBlock.z = result.z;
			// determine the adjacent block
			int intPosCurX = (int)floor(posCur.x);
			int intPosCurY = (int)floor(posCur.y);
			int intPosCurZ = (int)floor(posCur.z);
			double fracPosCurX = posCur.x - (double)intPosCurX;
			double fracPosCurY = posCur.y - (double)intPosCurY;
			double fracPosCurZ = posCur.z - (double)intPosCurZ;
			selBlockAdj.x = selBlock.x;
			selBlockAdj.y = selBlock.y;
			selBlockAdj.z = selBlock.z;
			if (hasJustTraversedPositively(fracPosCurX))
				selBlockAdj.x = intPosCurX - 1;
			else if (hasJustTraversedNegatively(fracPosCurX))
				selBlockAdj.x = intPosCurX + 1;
			else if (hasJustTraversedPositively(fracPosCurY))
				selBlockAdj.y = intPosCurY - 1;
			else if (hasJustTraversedNegatively(fracPosCurY))
				selBlockAdj.y = intPosCurY + 1;
			else if (hasJustTraversedPositively(fracPosCurZ))
				selBlockAdj.z = intPosCurZ - 1;
			else if (hasJustTraversedNegatively(fracPosCurZ))
				selBlockAdj.z = intPosCurZ + 1;
			return;
		}
	}
	selBlock.x = -1;
	selBlock.y = -1;
	selBlock.z = -1;
	selBlockAdj.x = -1;
	selBlockAdj.y = -1;
	selBlockAdj.z = -1;
}

void SelectFrame::render()
{
	TextureManager::get(indexTexCursor).bind();
	bidRenderer->render(glm::ivec2(400, 300), glm::ivec2(32, 32));
}