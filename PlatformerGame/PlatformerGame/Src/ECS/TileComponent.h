#pragma once

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <SDL.h>
#include "../TextureManager.h"

class TileComponent : public Component
{
public:

	TileComponent() = default;

	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
		}
		transform = &entity->getComponent<TransformComponent>();

		if (!entity->hasComponent<SpriteComponent>())
		{
			entity->addComponent<SpriteComponent>(tileAssets[tileID]);
		}
		sprite = &entity->getComponent<SpriteComponent>();
	}

	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	int tileID;

	const char* tileAssets[3] = { "Assets/dirt.png",
							 "Assets/grass.png",
							 "Assets/water.png" };

};