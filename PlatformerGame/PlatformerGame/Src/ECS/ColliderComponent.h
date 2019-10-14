#pragma once

#include <string>
#include <SDL.h>
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component
{
public:

	ColliderComponent(std::string s, int xOff, int yOff, int w, int h, bool dynamic = false) : tag(s), isDynamic(dynamic), width(w), height(h)
	{
		xOffset = xOff;
		yOffset = yOff;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		collider.x = (int)transform->position.x + xOffset;
		collider.y = (int)transform->position.y + yOffset;
		collider.w = width * transform->scale;
		collider.h = height * transform->scale;

		tex = TextureManager::LoadTexture("Assets/colTex.png");
		srcRect = { 0, 0, Config::TILE_SIZE, Config::TILE_SIZE};
		dstRect = { collider.x, collider.y, collider.w, collider.h };
	}

	void update() override
	{
		if (isDynamic)
		{
			collider.x = (int)transform->position.x + xOffset;
			collider.y = (int)transform->position.y + yOffset;
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
	bool isDynamic = false;
	int width;
	int height;
	int xOffset;
	int yOffset;
};