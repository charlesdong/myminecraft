#ifndef WORLD_H_
#define WORLD_H_

#include "cuberenderer.h"

class World
{
private:
	static const int X = 10;
	static const int Y = 2;
	static const int Z = 10;

	int blocks[X][Y][Z];
	CubeRenderer renderer;
public:
	World();
	void init();
	void render(const Camera & cam);
	void clear();
};

#endif