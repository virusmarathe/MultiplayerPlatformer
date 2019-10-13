#pragma once

#include "ECS.h"
#include <SDL.h>
#include "../Config.h"

class TileComponent : public Component
{
public:

	TileComponent() = default;

	TileComponent(int srcX, int srcY, int xpos, int ypos, const char * tileMap)
	{
		texture = TextureManager::LoadTexture(tileMap);

		position.x = xpos;
		position.y = ypos;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = Config::TILE_SIZE;

		dstRect.x = xpos;
		dstRect.y = ypos;
		dstRect.w = dstRect.h = Config::TILE_SIZE * Config::MAP_SCALE;
	}

	~TileComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, dstRect, SDL_FLIP_NONE);
	}

	void update() override
	{
		dstRect.x = position.x - Game::camera.x;
		dstRect.y = position.y - Game::camera.y;
	}

public:
	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;
	Vector2D position;
};