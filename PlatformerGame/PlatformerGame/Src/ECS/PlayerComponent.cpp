#include "PlayerComponent.h"

void PlayerComponent::init()
{
	entity->addComponent<TransformComponent>(200.0f, 1400.0f, 4);
	entity->addComponent<SpriteComponent>("Assets/player_anims.png", true);
	entity->addComponent<KeyboardController>();
	entity->addComponent<ColliderComponent>("player", 40, 35, 10, Config::TILE_SIZE - 10, true);
	entity->addGroup(Game::groupLabels::LAYER_PLAYER);
	entity->getComponent<AnimationComponent>().AddAnimation(IDLE, &idle);
	entity->getComponent<AnimationComponent>().AddAnimation(WALK, &walk);
	entity->getComponent<AnimationComponent>().play(IDLE);
	transform = &entity->getComponent<TransformComponent>();
	transform->acceleration.y = GRAVITY;
	collider = &entity->getComponent<ColliderComponent>();
	startPosition = transform->position;
}

void PlayerComponent::update()
{
	Vector2D playerVel = entity->getComponent<TransformComponent>().velocity;
	if (playerVel.x < 0)
	{
		entity->getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		entity->getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_NONE;
	}

	if (playerVel.x != 0 || playerVel.y != 0)
	{
		entity->getComponent<AnimationComponent>().play(WALK);
	}
	else
	{
		entity->getComponent<AnimationComponent>().play(IDLE);
	}

	if (isJumping)
	{
		timer += 1.0/Config::FPS;
		if (timer > 0.2)
		{
			isJumping = false;
		}
	}
	else if (isGrounded)
	{
		transform->acceleration.y = 0;
		transform->velocity.y = 0;
		timer = 0;
	}
	else
	{
		transform->acceleration.y = GRAVITY;
	}
}

void PlayerComponent::doJump()
{
	isJumping = true;
	isGrounded = false;
	transform->acceleration.y = -3000.0f;
	transform->velocity.y = -100.0f;
}

void PlayerComponent::restartPlayer()
{
	transform->position = startPosition;
}
