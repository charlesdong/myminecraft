#ifndef SELECTFRAME_H_
#define SELECTFRAME_H_

#include <glm/glm.hpp>
#include "camera.h"
#include "cuberenderer.h"
#include "bidimensionalrenderer.h"
#include "world.h"

class SelectFrame
{
private:
	// pointers
	const Camera * pCamera;
	CubeRenderer * pCubeRenderer;
	BidimensionalRenderer * pBidRenderer;
	World * pWorld;

	// selection
	double selPrecision;
	double selDistance;
	glm::ivec3 selBlock;

	// textures
	int indexTexCursor;

	void select();
public:
	SelectFrame();
	void init(const Camera * pCam, CubeRenderer * pCubeRendererArg, BidimensionalRenderer * pBidRendererArg, World * pWorldArg);
	void update();
	void render();
};

#endif