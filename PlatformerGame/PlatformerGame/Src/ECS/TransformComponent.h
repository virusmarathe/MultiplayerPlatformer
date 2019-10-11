#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:

	TransformComponent() : position(0, 0) {}
	TransformComponent(float x, float y) : position(x, y) {}
	TransformComponent(float x, float y, int s) : position(x, y), scale(s) {}
	TransformComponent(float x, float y, int h, int w, int s) : position(x,y), width(w), height(h), scale(s) {}

	void init() override
	{
		velocity.Zero();
	}

	void update() override
	{
		position += (velocity);
	}

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;
};