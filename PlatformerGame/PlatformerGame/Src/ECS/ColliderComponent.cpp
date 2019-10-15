#include "ColliderComponent.h"

void ColliderComponent::init()
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
	srcRect = { 0, 0, Config::TILE_SIZE, Config::TILE_SIZE };
	dstRect = { collider.x, collider.y, collider.w, collider.h };
}

void ColliderComponent::update()
{
	if (isDynamic)
	{
		collider.x = (int)transform->position.x + xOffset;
		collider.y = (int)transform->position.y + yOffset;
	}

	dstRect.x = collider.x - Game::camera.x;
	dstRect.y = collider.y - Game::camera.y;
}
