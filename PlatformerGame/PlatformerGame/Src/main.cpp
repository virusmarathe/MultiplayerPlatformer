#include <SDL.h>
#include "Game.h"
#include "Config.h"

Game* game = NULL;

int main(int argc, char* args[])
{
	const int frameDelay = 1000 / Config::FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("Platformer Test", 50, 50, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	delete game;
	game = NULL;

	return 0;
}