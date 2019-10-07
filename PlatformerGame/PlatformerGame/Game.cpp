#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

#define SDL_ERROR(s) std::cout << s << " SDL Error: " << SDL_GetError() << std::endl

GameObject* m_Player;
SDL_Renderer* Game::renderer = NULL;
Map* map;

Game::Game() :mb_isRunning(false), m_Window(NULL)
{
}

Game::~Game()
{
	clean();
}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_Window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (m_Window)
		{
			renderer = SDL_CreateRenderer(m_Window, -1, 0);
			if (renderer)
			{
				SDL_SetRenderDrawColor(renderer, 71, 142, 181, 0xFF);
				mb_isRunning = true;
				m_Player = new GameObject("Assets/player.png", 100, 100, 4);
				map = new Map();
			}
			else
			{
				SDL_ERROR("Renderer could not brea created!");
			}
		}
		else
		{
			SDL_ERROR("Window could not be created!");
		}
	}
	else
	{
		SDL_ERROR("SDL could not initialize!");
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
			case SDL_QUIT: mb_isRunning = false; break;
			default: break;
		}
	}
}

void Game::update(float dt)
{
	m_Player->Update(dt);
}

void Game::render()
{
	SDL_RenderClear(renderer);

	map->DrawMap();
	m_Player->Render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete m_Player;
	m_Player = NULL;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
	std::cout << "Game cleaned." << std::endl;
}
