#ifndef DEBUGSCREEN_H_
#define DEBUGSCREEN_H_

#include "player.h"
#include "selectframe.h"
#include "textrenderer.h"

class DebugScreen
{
private:
	bool isShown;
	const Player * player;
	const SelectFrame * selFrame;
	TextRenderer * textRenderer;
public:
	DebugScreen();
	void init(const Player * pCam, const SelectFrame * pSelFrame, TextRenderer * pTexRenderer);
	void update();
	void render();
};

#endif