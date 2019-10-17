#include "TransformComponent.h"

void TransformComponent::init()
{
	velocity.Zero();
	acceleration.Zero();
	m_Colliders = manager.getGroup(Game::LAYER_COLLIDERS);
}

void TransformComponent::update()
{
	// delta t is always 1000/60 ms or 1/60 seconds, if switch to variable framerate need send dt to update
	double dt = 1.0 / Config::FPS;
	velocity += acceleration * dt;
	position += (velocity) * dt;
}
