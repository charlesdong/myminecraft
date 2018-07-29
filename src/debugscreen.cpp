#include "debugscreen.h"
#include "game.h"
// sorry, I would prefer to use C++ tools rather than C ones,
// but the format string is really convenient
#include <cstdio>

DebugScreen::DebugScreen()
{
	isShown = true;		// DEBUGGING
}

void DebugScreen::init(const Camera * pCam, TextRenderer * pTextRenderer)
{
	camera = pCam;
	textRenderer = pTextRenderer;
}

void DebugScreen::update()
{
	static bool pressF2 = false;
	if (pGame->isKeyDown(GLFW_KEY_F2))
	{
		if (!pressF2)
		{
			//isShown = !isShown;
			pressF2 = true;
		}
	}
	else
		pressF2 = false;
}

void DebugScreen::render()
{
	if (!isShown)
		return;

	glm::dvec3 position = camera->getPlayerPos();

	char buffer[100];
	sprintf_s(
		buffer,
		"MyMinecraft 0.3\n"
		"FPS: %d\n"
		"X: %.3lf\n"
		"Y: %.3lf\n"
		"Z: %.3lf\n",
		pGame->getFps(),
		camera->getPlayerPos().x,
		camera->getPlayerPos().y,
		camera->getPlayerPos().z
	);
	textRenderer->render(buffer);
}