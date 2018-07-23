#include "cuberenderer.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "blockmanager.h"
#include "texturemanager.h"

CubeRenderer::CubeRenderer()
{
}

void CubeRenderer::init()
{
	prog.load("shaders/shader.vert", "shaders/shader.frag");
	loadTextures();

	const float vertexes[] =
	{
		// back face
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

		// front face
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

		// left face
		-0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 1.0f,

		// right face
		0.5f,  0.5f,  0.5f,		0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,		0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		0.0f, 1.0f,

		// bottom face
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

		// top face
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f
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

void CubeRenderer::beginRender(long x, long y, long z, const Camera & cam, int bId)
{
	// calculate the model-view-projection matrix
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(float(x), float(y), float(z)));
	glm::mat4 view = glm::lookAt(cam.getEyePos(), cam.getEyePos() + cam.getFront(), cam.getUp());
	// TODO: magic numbers
	glm::mat4 proj = glm::perspective(45.0f, (float)800.0f / (float)600.0f, 0.1f, 100.0f);
	glm::mat4 mat = proj * view * model;

	// active program and texture
	prog.use();
	prog.setMat4f("mat", mat);

	// TODO: pass by reference
	blockId = bId;
	bd = blockMgr.getBlockData(blockId);

	glBindVertexArray(vao);
}

void CubeRenderer::render(int face) const
{
	prog.setVec3f("color_aux", glm::vec3(1.0f, 1.0f, 1.0f));
	if (face == TOP)
	{
		if (blockId == 2)	// TODO: MN
			prog.setVec3f("color_aux", glm::vec3(0.71f, 1.18f, 0.34f));
		TextureManager::get(bd.texTop).bind();
	}
	else if (face == BOTTOM)
		TextureManager::get(bd.texBottom).bind();
	else
		TextureManager::get(bd.texSide).bind();
	glDrawArrays(GL_TRIANGLES, face * 6, 6);
}

void CubeRenderer::clear()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void CubeRenderer::loadTextures()
{
	// register dirt block
	blockMgr.load("dirt.png");
	// register grass block
	blockMgr.load("grass_side.png", "grass_top.png", "dirt.png");
	// register bedrock block
	blockMgr.load("bedrock.png");
}