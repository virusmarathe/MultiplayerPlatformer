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
int cameraBoundX = 300;
int cameraBoundY = 200;

auto& tiles(manager.getGroup(Game::LAYER_MAP));
auto& players(manager.getGroup(Game::LAYER_PLAYER));
auto& colliders(manager.getGroup(Game::LAYER_COLLIDERS));

SDL_Rect Game::camera = { 0,0, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT };

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
				setup();
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

void Game::setup()
{
	map = new Map(Config::TILEMAP_FILENAME);
	map->LoadMap(Config::LEVEL0_MAP_FILENAME);
	cameraBoundX = (map->width * Config::TILE_SIZE * Config::MAP_SCALE) - camera.w;
	cameraBoundY = (map->height * Config::TILE_SIZE * Config::MAP_SCALE) - camera.h;
	m_Player.addComponent<PlayerComponent>();
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
	Vector2D playerPos = m_Player.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	SDL_Rect playerCol = m_Player.getComponent<ColliderComponent>().collider;
	Vector2D playerVel = m_Player.getComponent<TransformComponent>().velocity;
	playerCol.x += playerVel.x;
	playerCol.y += playerVel.y;

	SDL_Rect groundCheck = m_Player.getComponent<ColliderComponent>().collider;
	groundCheck.y += Config::TILE_SIZE / 4.0f;
	bool onGround = false;
	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCol, playerCol))
		{
			m_Player.getComponent<TransformComponent>().position = playerPos;
		}

		if (Collision::AABB(cCol, groundCheck))
		{
			onGround = true;
		}
	}
	m_Player.getComponent<PlayerComponent>().isGrounded = onGround;

	camera.x = (int)(m_Player.getComponent<TransformComponent>().position.x) - (camera.w / 4);
	camera.y = (int)(m_Player.getComponent<TransformComponent>().position.y) - (camera.h / 2);

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > cameraBoundX) camera.x = cameraBoundX;
	if (camera.y > cameraBoundY) camera.y = cameraBoundY;

	if (!Collision::AABB(m_Player.getComponent<ColliderComponent>().collider, camera))
	{
		m_Player.getComponent<PlayerComponent>().restartPlayer();
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& c : colliders)
	{
		c->draw();
	}

	for (auto& p : players)
	{
		p->draw();
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
