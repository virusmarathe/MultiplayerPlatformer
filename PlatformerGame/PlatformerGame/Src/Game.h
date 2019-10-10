#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update(float dt);
	void render();
	void clean();
	bool running() { return mb_isRunning; }

	static SDL_Renderer* renderer;
private:

	bool mb_isRunning;
	SDL_Window* m_Window;
};
