#ifndef BIDIMENSIONALRENDERER_H_
#define BIDIMENSIONALRENDERER_H_

#include "program.h"
#include <glm/glm.hpp>

class BidimensionalRenderer
{
private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	Program prog;
public:
	BidimensionalRenderer();
	void init();
	void render(
		const glm::ivec2 & position,
		const glm::ivec2 & size,
		const float txmin = 0.0f,
		const float txmax = 1.0f,
		const float tymin = 0.0f,
		const float tymax = 1.0f,
		bool centralized = true
	);
	void clear();
};

#endif