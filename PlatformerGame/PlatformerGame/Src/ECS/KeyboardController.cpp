#include "KeyboardController.h"

void KeyboardController::init()
{
	transform = &entity->getComponent<TransformComponent>();
	player = &entity->getComponent<PlayerComponent>();
	speed = Config::PLAYER_SPEED;
}

void KeyboardController::update()
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	//if (state[SDL_SCANCODE_S]) y = 1.0f;
	if (state[SDL_SCANCODE_A]) x = -1.0f;
	if (state[SDL_SCANCODE_D]) x = 1.0f;

	//if (!state[SDL_SCANCODE_W] && !state[SDL_SCANCODE_S]) y = 0;
	if (!state[SDL_SCANCODE_A] && !state[SDL_SCANCODE_D]) x = 0;

	transform->velocity = Vector2D(x, y).normalize() * speed;

	if (state[SDL_SCANCODE_W])
	{
		if (player->isGrounded)
		{
			player->doJump();
		}
	}
}
