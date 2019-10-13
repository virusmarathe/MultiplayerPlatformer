#pragma once

#include <string>
#include <SDL.h>
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component
{
public:

	ColliderComponent(std::string s) : tag(s) { }

	ColliderComponent(std::string s, int xPos, int yPos) : tag(s)
	{
		collider.x = xPos;
		collider.y = yPos;
		collider.w = collider.h = Config::TILE_SIZE * Config::MAP_SCALE;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		tex = TextureManager::LoadTexture("Assets/colTex.png");
		srcRect = { 0, 0, Config::TILE_SIZE * Config::MAP_SCALE, Config::TILE_SIZE};
		dstRect = { collider.x, collider.y, collider.w, collider.h };
	}

	void update() override
	{
		if (tag != "terrain") // to be changed to static/dynamic
		{
			collider.x = (int)transform->position.x;
			collider.y = (int)transform->position.y;
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}

		dstRect.x = collider.x - Game::camera.x;
		dstRect.y = collider.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::Draw(tex, srcRect, dstRect, SDL_FLIP_NONE);
	}

	SDL_Rect collider;
	std::string tag;
	TransformComponent* transform;
	SDL_Texture* tex;
	SDL_Rect srcRect, dstRect;
};