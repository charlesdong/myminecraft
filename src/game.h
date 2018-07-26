#ifndef GAME_H_
#define GAME_H_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "camera.h"
#include "cuberenderer.h"
#include "bidimensionalrenderer.h"
#include "world.h"
#include "selectframe.h"

#define pGame (Game::getPointer())

class Game
{
private:
	GLFWwindow * window;
	CubeRenderer cubeRenderer;
	BidimensionalRenderer bidRenderer;
	Camera camera;
	World world;
	SelectFrame selFrame;
	int fps;

	void init();
	void loop();
	void clear();

	void update();
	void render();

	static Game * game;
public:
	Game();
	void run();

	bool isKeyDown(int key) const
	{
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	bool isMouseButtonDown(int button) const
	{
		return glfwGetMouseButton(window, button) == GLFW_PRESS;
	}

	glm::dvec2 getCursorPos() const;

	static Game * getPointer()
	{
		return game;
	}
};

#endif