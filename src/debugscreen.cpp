#include "debugscreen.h"
#include "game.h"
// Sorry, I would prefer to use C++ tools rather than C ones,
// but the format string is really convenient.
#include <cstdio>

DebugScreen::DebugScreen()
{
	isShown = false;
}

void DebugScreen::init(const Player * pPlayer, const SelectFrame * pSelFrame, TextRenderer * pTextRenderer)
{
	player = pPlayer;
	selFrame = pSelFrame;
	textRenderer = pTextRenderer;
}

void DebugScreen::update()
{
	static bool pressF3 = false;
	if (pGame->isKeyDown(GLFW_KEY_F3))
	{
		if (!pressF3)
		{
			isShown = !isShown;
			pressF3 = true;
		}
	}
	else
		pressF3 = false;
}

void DebugScreen::render() const
{
	if (!isShown)
		return;

	glm::dvec3 position = player->getPosition();
	glm::dvec3 velocity = player->getVelocity();
	glm::ivec3 selBlock = selFrame->getSelBlock();
	glm::ivec3 selBlockAdj = selFrame->getSelBlockAdj();

	char buffer[200];
	sprintf_s(
		buffer,
		"MyMinecraft 0.3\n"
		"FPS: %d\n"
		"X: %.3lf\n"
		"Y: %.3lf\n"
		"Z: %.3lf\n"
		"VelocityX: %.3lf\n"
		"VelocityY: %.3lf\n"
		"VelocityZ: %.3lf\n"
		"Pitch: %.1lf\n"
		"Yaw: %.1lf\n"
		"Selected block: %d %d %d\n"
		"Adjacent block: %d %d %d",
		pGame->getFps(),
		position.x,
		position.y,
		position.z,
		velocity.x,
		velocity.y,
		velocity.z,
		player->getPitch(),
		player->getYaw(),
		selBlock.x, selBlock.y, selBlock.z,
		selBlockAdj.x, selBlockAdj.y, selBlockAdj.z
	);
	textRenderer->render(buffer);
}