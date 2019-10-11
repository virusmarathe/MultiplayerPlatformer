#pragma once

#include "../Game.h"
#include "Components.h"

class KeyboardController : public Component
{
public:

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_W]) y = -1.0f;
		if (state[SDL_SCANCODE_A]) x = -1.0f;
		if (state[SDL_SCANCODE_S]) y = 1.0f;
		if (state[SDL_SCANCODE_D]) x = 1.0f;

		if (!state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S]) y = 0;
		if (!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]) x = 0;

		transform->velocity = Vector2D(x, y).normalize() * speed;
	}

	TransformComponent* transform;
	float x = 0;
	float y = 0;
	float speed = 5.0f;
};
