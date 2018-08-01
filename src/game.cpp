#include "game.h"
#include <cstdlib>
#include <cstdio>

Game * Game::game = nullptr;
const char * Game::version = "0.4";

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
	double timeStart = glfwGetTime();

	if (!glfwInit())
	{
		logger.log(FATAL, "Failed to init GLFW!");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// TODO: magic number "800" and "600"
	window = glfwCreateWindow(800, 600, "MyMinecraft 0.3", nullptr, nullptr);
	if (!window)
	{
		logger.log(FATAL, "Failed to create window using GLFW!");
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		logger.log(FATAL, "Failed to init GLEW!");
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.51f, 0.68f, 1.0f, 1.0f);		// sky color values (from a pixel from a screenshot)

	cubeRenderer.init();
	renderBlock.init(&cubeRenderer);
	world.init(&renderBlock);
	selFrame.init(&player, &bidRenderer, &world);
	bidRenderer.init();
	textRenderer.init(&bidRenderer);
	debugScreen.init(&player, &selFrame, &textRenderer);
	player.init(&world);

	fps = 0;

	double timeEnd = glfwGetTime();
	char logInfo[64];
	sprintf_s(logInfo, "Game initialized successfully, time used: %d ms", (int)((timeEnd - timeStart) * 1000.0));
	logger.log(INFO, logInfo);
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
	bidRenderer.clear();
}

void Game::update()
{
	// update deltaTime
	static int timeInt = int(glfwGetTime());
	static double timeLast = 0.0;
	double timeCur = glfwGetTime();
	deltaTime = timeCur - timeLast;
	timeLast = timeCur;

	// update FPS
	if (timeCur - timeInt < 1.0)
		frames++;
	else
	{
		fps = frames;
		frames = 0;
		timeInt = int(glfwGetTime());
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	selFrame.update();
	debugScreen.update();
	player.update();
}

void Game::render() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	world.render(player.getEyePosition(), player.getFrontInScene(), player.getUp());
	selFrame.render();
	debugScreen.render();
}

glm::dvec2 Game::getCursorPos() const
{
	glm::dvec2 cpos;
	glfwGetCursorPos(window, &cpos.x, &cpos.y);
	return cpos;
}