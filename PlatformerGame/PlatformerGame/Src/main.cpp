#include <SDL.h>
#include "Game.h"

Game* game = NULL;

int main(int argc, char* args[])
{
	Uint32 frameTime = 0;
	Uint32 prevFrameTime = 0;
	float deltaTime = 0;
	game = new Game();
	game->init("test", 50, 50, 1280, 960, false);

	while (game->running())
	{
		frameTime = SDL_GetTicks();
		deltaTime = frameTime - prevFrameTime;
		game->handleEvents();
		game->update(deltaTime);
		game->render();
		prevFrameTime = frameTime;
	}

	delete game;
	game = NULL;

	return 0;
}