#pragma once

#include "Components.h"
#include <SDL.h>

class SpriteComponent : public Component
{
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTexture(const char* path)
	{
		if (texture != NULL) SDL_DestroyTexture(texture);

		texture = TextureManager::LoadTexture(path);
	}

	void init() override
	{
		position = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 32;
		dstRect.w = dstRect.h = 64;
	}

	void update(float dt) override
	{
		dstRect.x = (int)position->x();
		dstRect.y = (int)position->y();
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, dstRect);
	}

private:
	TransformComponent* position;
	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;
};