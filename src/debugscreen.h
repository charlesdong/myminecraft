#ifndef DEBUGSCREEN_H_
#define DEBUGSCREEN_H_

#include "player.h"
#include "textrenderer.h"

class DebugScreen
{
private:
	bool isShown;
	const Player * player;
	TextRenderer * textRenderer;
public:
	DebugScreen();
	void init(const Player * pCam, TextRenderer * pTexRenderer);
	void update();
	void render();
};

#endif