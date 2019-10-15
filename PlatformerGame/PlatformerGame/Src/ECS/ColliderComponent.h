#pragma once

#include <string>
#include <SDL.h>
#include "Components.h"
#include "../TextureManager.h"

class TransformComponent;

class ColliderComponent : public Component
{
public:

	ColliderComponent(std::string s, int xOff, int yOff, int w, int h, bool dynamic = false) : tag(s), isDynamic(dynamic), width(w), height(h)
	{
		xOffset = xOff;
		yOffset = yOff;
	}

	void init() override;


	void update() override;


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