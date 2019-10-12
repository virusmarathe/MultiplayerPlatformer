#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"

#define SDL_ERROR(s) std::cout << s << " SDL Error: " << SDL_GetError() << std::endl

SDL_Renderer* Game::renderer = NULL;
SDL_Event Game::event;

Map* map;
EntityManager manager;
auto& m_Player(manager.addEntity());
Animation idle = Animation(0, 3, 100);
Animation walk = Animation(1, 8, 100);

enum PlayerAnims
{
	IDLE,
	WALK
};

std::vector<ColliderComponent*> Game::colliders;

enum groupLabels : std::size_t
{
	LAYER_MAP,
	LAYER_PLAYER,
	LAYER_ENEMY
};

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
			renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer)
			{
				SDL_SetRenderDrawColor(renderer, 71, 142, 181, 0xFF);
				mb_isRunning = true;
				map = new Map();
				Map::LoadMap("Assets/testmap1024.map", 32, 32);
				m_Player.addComponent<TransformComponent>(50.0f, 50.0f, 2);
				m_Player.addComponent<SpriteComponent>("Assets/player_anims.png", true);
				m_Player.addComponent<KeyboardController>();
				m_Player.addComponent<ColliderComponent>("player");
				m_Player.addGroup(groupLabels::LAYER_PLAYER);
				m_Player.getComponent<AnimationComponent>().AddAnimation(IDLE, &idle);
				m_Player.getComponent<AnimationComponent>().AddAnimation(WALK, &walk);
				m_Player.getComponent<AnimationComponent>().play(IDLE);
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
	if (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
			case SDL_QUIT: mb_isRunning = false; break;
			default: break;
		}
	}
}

void Game::update()
{
	manager.refresh();
	manager.update();

	if (m_Player.getComponent<TransformComponent>().velocity.x < 0)
	{
		m_Player.getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		m_Player.getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_NONE;
	}

	if (m_Player.getComponent<TransformComponent>().velocity.x != 0 || m_Player.getComponent<TransformComponent>().velocity.y != 0)
	{
		m_Player.getComponent<AnimationComponent>().play(WALK);
	}
	else
	{
		m_Player.getComponent<AnimationComponent>().play(IDLE);
	}

	for (auto col : colliders)
	{
		if (Collision::AABB(m_Player.getComponent<ColliderComponent>(), *col))
		{
			//m_Player.getComponent<TransformComponent>().velocity *= -1.f;
		}
	}

}

auto& tiles(manager.getGroup(LAYER_MAP));
auto& players(manager.getGroup(LAYER_PLAYER));
auto& enemies(manager.getGroup(LAYER_ENEMY));

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& e : enemies)
	{
		e->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete map;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
	std::cout << "Game cleaned." << std::endl;
}

void Game::AddTile(int id, int x, int y)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupLabels::LAYER_MAP);
}
