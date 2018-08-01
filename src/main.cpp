#include "game.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")	// disable the console
int main()
{
	Game game;
	game.run();
	return 0;
}