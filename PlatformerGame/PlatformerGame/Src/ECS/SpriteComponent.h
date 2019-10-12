#pragma once

#include "Components.h"
#include <SDL.h>
#include "../TextureManager.h"

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

	void init() override
	{
		if (animated)
		{
			if (!entity->hasComponent<AnimationComponent>())
			{
				entity->addComponent<AnimationComponent>();
			}
			animator = &entity->getComponent<AnimationComponent>();
		}
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / animator->timePerFrame) % animator->frames);
			srcRect.y = animator->animIndex * transform->height;
		}

		dstRect.x = (int)transform->position.x;
		dstRect.y = (int)transform->position.y;
		dstRect.w = transform->width * transform->scale;
		dstRect.h = transform->height * transform->scale;
	}

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