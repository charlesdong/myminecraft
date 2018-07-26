#include "bidimensionalrenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

BidimensionalRenderer::BidimensionalRenderer()
{
}

void BidimensionalRenderer::init()
{
	prog.load("shaders/bidimensional.vert", "shaders/bidimensional.frag");

	const float vertexes[] =
	{
		0.5f, 0.5f,		1.0f, 1.0f,
		-0.5f, 0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f,	0.0f, 0.0f,
		0.5f, -0.5f,	1.0f, 0.0f
	};

	const unsigned int indexes[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BidimensionalRenderer::render(const glm::ivec2 & position, const glm::ivec2 & size)
{
	glm::mat4 model;
	model = glm::translate(model, glm::vec3((float)position.x, (float)position.y, 0.0f));
	model = glm::scale(model, glm::vec3((float)size.x, (float)size.y, 1.0f));

	static glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);		// TODO: magic numbers

	glm::mat4 mat = proj * model;

	prog.use();
	prog.setMat4f("mat", mat);

	glm::vec4 v = mat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	// QUESTION: Is glDisable(GL_DEPTH_TEST) needed?

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void BidimensionalRenderer::clear()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}