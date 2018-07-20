#ifndef GAME_H_
#define GAME_H_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "camera.h"
#include "world.h"

class Game
{
private:
	GLFWwindow * window;
	Camera camera;
	World world;

	void init();
	void loop();
	void clear();

	void update();
	void render();
public:
	Game();
	void run();
};

#endif