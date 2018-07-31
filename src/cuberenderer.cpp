#include "cuberenderer.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "blockmanager.h"
#include "texturemanager.h"

#include <iostream>
using std::cout;

CubeRenderer::CubeRenderer()
{
}

void CubeRenderer::init()
{
	prog.load("shaders/shader.vert", "shaders/shader.frag");
	initCubeRendering();
}

void CubeRenderer::initCubeRendering()
{
	const float vertexes[] =
	{
		// back face
		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		1.0f,  0.0f, 0.0f,	1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,		1.0f, 1.0f,
		0.0f,  0.0f, 0.0f,	0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.0f, 1.0f,

		// front face
		0.0f, 0.0f,  1.0f,	0.0f, 0.0f,
		1.0f, 0.0f,  1.0f,		1.0f, 0.0f,
		1.0f,  1.0f,  1.0f,		1.0f, 1.0f,
		1.0f,  1.0f,  1.0f,		1.0f, 1.0f,
		0.0f,  1.0f,  1.0f,	0.0f, 1.0f,
		0.0f, 0.0f,  1.0f,	0.0f, 0.0f,

		// left face
		0.0f,  1.0f,  1.0f,	1.0f, 1.0f,
		0.0f,  1.0f, 0.0f,	0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		0.0f, 0.0f,  1.0f,	1.0f, 0.0f,
		0.0f,  1.0f,  1.0f,	1.0f, 1.0f,

		// right face
		1.0f,  1.0f,  1.0f,		0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,		0.0f, 1.0f,
		1.0f, 0.0f,  1.0f,		0.0f, 0.0f,

		// bottom face
		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		1.0f, 0.0f,  1.0f,		1.0f, 0.0f,
		1.0f, 0.0f,  1.0f,		1.0f, 0.0f,
		0.0f, 0.0f,  1.0f,	0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,	0.0f, 1.0f,

		// top face
		0.0f,  1.0f, 0.0f,	0.0f, 1.0f,
		1.0f,  1.0f, 1.0f,		1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,		1.0f, 1.0f,
		1.0f,  1.0f, 1.0f,		1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,	0.0f, 1.0f,
		0.0f,  1.0f, 1.0f,		0.0f, 0.0f
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CubeRenderer::beginRender(long x, long y, long z, const glm::dvec3 & eyePosition, const glm::dvec3 & frontInScene, const glm::dvec3 & up)
{
	// Calculate the model-view-projection matrix.
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(float(x), float(y), float(z)));
	//std::cout << player << std::endl;
	glm::mat4 view = glm::lookAt(
		eyePosition,
		eyePosition + frontInScene,
		up
	);

	// TODO: magic numbers
	// NOTE: OPTIMIZATION: "proj" rarely changes, make it static
	static glm::mat4 proj = glm::perspective(45.0f, (float)800.0f / (float)600.0f, 0.1f, 100.0f);
	glm::mat4 mat = proj * view * model;

	// active program and texture
	prog.use();
	prog.setMat4f("mat", mat);

	glEnable(GL_DEPTH_TEST);

	glBindVertexArray(vao);
}

void CubeRenderer::render(int face) const
{
	glDrawArrays(GL_TRIANGLES, face * 6, 6);
}

void CubeRenderer::clear()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}