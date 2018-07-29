#ifndef DEBUGSCREEN_H_
#define DEBUGSCREEN_H_

#include "camera.h"
#include "textrenderer.h"

class DebugScreen
{
private:
	bool isShown;
	const Camera * camera;
	TextRenderer * textRenderer;
public:
	DebugScreen();
	void init(const Camera * pCam, TextRenderer * pTexRenderer);
	void update();
	void render();
};

#endif