#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Config.h"

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return mb_isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static SDL_Rect camera;

	enum groupLabels : std::size_t
	{
		LAYER_MAP,
		LAYER_PLAYER,
		LAYER_COLLIDERS
	};

private:

	bool mb_isRunning;
	SDL_Window* m_Window;
};

