#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"

#define SDL_ERROR(s) std::cout << s << " SDL Error: " << SDL_GetError() << std::endl

SDL_Renderer* Game::renderer = NULL;
Map* map;
EntityManager manager;
auto& m_Player(manager.addEntity());

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
				map = new Map();
				m_Player.addComponent<TransformComponent>(50.0f, 50.0f);
				m_Player.addComponent<SpriteComponent>("Assets/player.png");
			}
			else
			{
				SDL_ERROR("Renderer could not be created!");
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
	manager.refresh();
	manager.update(dt);

	m_Player.getComponent<TransformComponent>().position.y += dt * 0.5f;

	if (m_Player.getComponent<TransformComponent>().position.y >= 800)
	{
		m_Player.getComponent<TransformComponent>().position.y = 0;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	map->DrawMap();
	manager.draw();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
	std::cout << "Game cleaned." << std::endl;
}
