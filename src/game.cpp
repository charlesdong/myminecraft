#include "game.h"
#include <iostream>
using std::cout;
using std::endl;

Game::Game()
{
}

void Game::run()
{
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
	window = glfwCreateWindow(800, 600, "MyMinecraft 0.1", nullptr, nullptr);
	if (window == nullptr)
		cout << "Failed to create window using GLFW!\n";
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		cout << "Failed to init GLEW!\n";

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.51f, 0.68f, 1.0f, 1.0f);		// sky color values (from a pixel from a screenshot)

	world.init();
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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	camera.newFrame();

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.move(LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.move(RIGHT);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.move(FRONT);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.move(BACK);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.move(UP);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.move(DOWN);
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	world.render(camera);
}