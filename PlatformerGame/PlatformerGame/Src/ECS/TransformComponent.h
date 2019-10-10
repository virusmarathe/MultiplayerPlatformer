#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:

	TransformComponent() : position(0, 0) {}
	TransformComponent(float x, float y) : position(x, y) {}

	void init() override
	{
		velocity.x = 0;
		velocity.y = 0;
	}

	void update(float dt) override
	{
		position += (velocity * (dt * speed));
	}

	Vector2D position;
	Vector2D velocity;

	float speed = 0.5f;
};