#pragma once
#include "Components.h"
#include "../Vector2D.h"
#include "../Config.h"

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

	int height = Config::TILE_SIZE;
	int width = Config::TILE_SIZE;
	int scale = 1;
};