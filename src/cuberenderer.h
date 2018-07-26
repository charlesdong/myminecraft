#ifndef CUBERENDERER_H_
#define CUBERENDERER_H_

#include <vector>

#include "camera.h"
#include "program.h"
#include "texture.h"
#include "blockmanager.h"

enum Face { BACK, FRONT, LEFT, RIGHT, BOTTOM, TOP };

class CubeRenderer
{
private:
	unsigned int vao;
	unsigned int vbo;
	Program prog;

	void initCubeRendering();
public:
	CubeRenderer();
	void init();
	void beginRender(long x, long y, long z, const Camera & cam);

	void setAuxColor(const glm::vec3 & color)
	{
		prog.setVec3f("color_aux", color);
	}

	void render(int face) const;
	void clear();
};

#endif