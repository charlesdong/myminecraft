#include "game.h"
#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;

Game * Game::game = nullptr;

Game::Game()
{
}

void Game::run()
{
	game = this;
	init();
	while (!glfwWindowShouldClose(window))
		loop();
	clear();
}

void Game::init()
{
	if (!glfwInit())
		cout << "Failed to init GLFW!\n";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// TODO: magic number "800" and "600"
	window = glfwCreateWindow(800, 600, "MyMinecraft 0.2", nullptr, nullptr);
	if (window == nullptr)
		cout << "Failed to create window using GLFW!\n";
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		cout << "Failed to init GLEW!\n";

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.51f, 0.68f, 1.0f, 1.0f);		// sky color values (from a pixel from a screenshot)

	world.init();

	fps = 0;
}

void Game::loop()
{
	update();
	render();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Game::clear()
{
	world.clear();
}

void Game::update()
{
	static int timeInt = int(glfwGetTime());
	double timeCur = glfwGetTime();
	if (timeCur - timeInt < 1.0)
		fps++;
	else
	{
		std::ostringstream oss;
		oss << "MyMinecraft 0.2 [FPS: " << fps << "]";
		glfwSetWindowTitle(window, oss.str().c_str());
		fps = 0;
		timeInt = int(timeCur);
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	camera.update();
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	world.render(camera);
}

glm::dvec2 Game::getCursorPos() const
{
	glm::dvec2 cpos;
	glfwGetCursorPos(window, &cpos.x, &cpos.y);
	return cpos;
}