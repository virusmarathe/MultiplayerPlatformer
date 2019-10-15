#pragma once

#include "Components.h"
#include <SDL.h>
#include "../TextureManager.h"

class TransformComponent;
class AnimationComponent;

class SpriteComponent : public Component
{
public:
	SpriteComponent() = default;
	SpriteComponent(const char* path, bool isAnimated = false)
	{
		animated = isAnimated;
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

	void init() override;

	void update() override;

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, dstRect, spriteFlip);
	}

public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

private:
	TransformComponent* transform;
	AnimationComponent* animator;
	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;
	bool animated = false;
};