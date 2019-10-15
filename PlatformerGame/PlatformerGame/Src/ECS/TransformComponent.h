#pragma once
#include "../Game.h"
#include "Components.h"
#include "../Vector2D.h"
#include "../Config.h"
#include "ColliderComponent.h"

extern EntityManager manager;
class ColliderComponent;

class TransformComponent : public Component
{
public:

	TransformComponent() : position(0, 0) {}
	TransformComponent(float x, float y) : position(x, y) {}
	TransformComponent(float x, float y, int s) : position(x, y), scale(s) {}
	TransformComponent(float x, float y, int h, int w, int s) : position(x,y), width(w), height(h), scale(s) {}

	void init() override;

	void update() override;

	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;

	ColliderComponent* collider;

	int height = Config::TILE_SIZE;
	int width = Config::TILE_SIZE;
	int scale = 1;
	std::vector<Entity*> m_Colliders;
	SDL_Rect playerCol;
	SDL_Rect floorChecker;

	bool isGrounded;

private:
	void checkCollisions(Vector2D prevPosition);
};