#include "SpriteComponent.h"

void SpriteComponent::init()
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

void SpriteComponent::update()
{
	if (animated)
	{
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / animator->timePerFrame) % animator->frames);
		srcRect.y = animator->animIndex * transform->height;
	}

	dstRect.x = (int)transform->position.x - Game::camera.x;
	dstRect.y = (int)transform->position.y - Game::camera.y;
	dstRect.w = transform->width * transform->scale;
	dstRect.h = transform->height * transform->scale;
}