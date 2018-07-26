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
	void render(const glm::ivec2 & position, const glm::ivec2 & size);
	void clear();
};

#endif