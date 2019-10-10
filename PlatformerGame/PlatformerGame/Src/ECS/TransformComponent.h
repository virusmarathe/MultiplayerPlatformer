#pragma once
#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:

	TransformComponent() : position(0,0) {}
	TransformComponent(float x, float y) : position(x,y) {}

	Vector2D position;
};