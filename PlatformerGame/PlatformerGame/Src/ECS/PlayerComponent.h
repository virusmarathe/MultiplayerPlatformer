#pragma once

#pragma once
#include "Components.h"
#include "../Config.h"
#include "../Game.h"
#include "../Vector2D.h"

extern EntityManager manager;
class TransformComponent;
class ColliderComponent;

class PlayerComponent : public Component
{
public:

	PlayerComponent() {}

	void init() override;

	void update() override;

	void doJump()
	{
		isJumping = true;
	}

	void restartPlayer();

	enum PlayerAnims
	{
		IDLE,
		WALK
	};

	TransformComponent* transform;
	ColliderComponent* collider;
	Animation idle = Animation(0, 3, 100);
	Animation walk = Animation(1, 8, 100);
	bool isGrounded = false;
	bool isJumping = false;
	const float GRAVITY = 9.0f;
	float timer = 0;
	SDL_Rect groundChecker;
	Vector2D startPosition;
};