#include "TransformComponent.h"

void TransformComponent::init()
{
	velocity.Zero();
	acceleration.Zero();
	m_Colliders = manager.getGroup(Game::LAYER_COLLIDERS);
}

void TransformComponent::update()
{
	velocity += acceleration;
	position += (velocity);
}
