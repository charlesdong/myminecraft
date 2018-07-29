#ifndef GAME_H_
#define GAME_H_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "camera.h"
#include "cuberenderer.h"
#include "bidimensionalrenderer.h"
#include "world.h"
#include "selectframe.h"
#include "textrenderer.h"
#include "debugscreen.h"

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
	TextRenderer textRenderer;
	DebugScreen debugScreen;

	static const char * version;

	int fps;			// FPS of last second
	int frames;			// number of frames counted in this second (have not passed)

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

	int getFps() const
	{
		return fps;
	}

	static Game * getPointer()
	{
		return game;
	}
};

#endif