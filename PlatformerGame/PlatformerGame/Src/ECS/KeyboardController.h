#pragma once

#include "../Game.h"
#include "Components.h"
#include "PlayerComponent.h"

class TransformComponent;
class PlayerComponent;

class KeyboardController : public Component
{
public:

	void init() override;

	void update() override;

	TransformComponent* transform;
	PlayerComponent* player;
	float x = 0;
	float y = 0;
	float speed = 1;
};
