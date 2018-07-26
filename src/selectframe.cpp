#include "selectframe.h"
#include "texturemanager.h"
#include "game.h"

SelectFrame::SelectFrame()
{
	pCamera = nullptr;
}

void SelectFrame::init(const Camera * pCam, CubeRenderer * pCubeRendererArg, BidimensionalRenderer * pBidRendererArg, World * pWorldArg)
{
	pCamera = pCam;
	pCubeRenderer = pCubeRendererArg;
	pBidRenderer = pBidRendererArg;
	pWorld = pWorldArg;
	selPrecision = 0.1;
	selDistance = 4.0;

	indexTexCursor = TextureManager::load("cursor");
}

void SelectFrame::update()
{
	select();
	if (selBlock.x != -1 || selBlock.y != -1 || selBlock.z != -1)
		if (pGame->isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
			pWorld->destroyBlock(selBlock.x, selBlock.y, selBlock.z);
}

void SelectFrame::select()
{
	glm::dvec3 posCur = pCamera->getEyePos();
	glm::ivec3 result(-1, -1, -1);				// Currently, a position of (-1, -1, -1) means "none selected"
	for (double dist = selPrecision; dist <= selDistance; dist += selPrecision)
	{
		posCur += pCamera->getFront() * selPrecision;
		result.x = (int)floor(posCur.x);
		result.y = (int)floor(posCur.y);
		result.z = (int)floor(posCur.z);
		if (pWorld->hasBlock(result.x, result.y, result.z))
		{
			selBlock.x = result.x;
			selBlock.y = result.y;
			selBlock.z = result.z;
			return;
		}
	}
	selBlock.x = -1;
	selBlock.y = -1;
	selBlock.z = -1;
}

void SelectFrame::render()
{
	/*
	pCubeRenderer->beginRender(selBlock.x, selBlock.y, selBlock.z, *pCamera);
	pCubeRenderer->setAuxColor(glm::vec3(1.0f, 1.0f, 1.0f));
	TextureManager::get(indexTexFrame).bind();
	for (int i = 0; i < 6; i++)
		pCubeRenderer->render(i);
		*/
	TextureManager::get(indexTexCursor).bind();
	pBidRenderer->render(glm::ivec2(400, 300), glm::ivec2(32, 32));
}