#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int xpos, int ypos, int scale) : mi_xPos(xpos), mi_yPos(ypos)
{
	m_ObjTexture = TextureManager::LoadTexture(textureSheet);
	int w, h;
	SDL_QueryTexture(m_ObjTexture, NULL, NULL, &w, &h);
	m_DstRect.x = mi_xPos;
	m_DstRect.y = mi_yPos;
	m_DstRect.w = w * scale;
	m_DstRect.h = h * scale;
}

GameObject::~GameObject()
{
	SDL_DestroyTexture(m_ObjTexture);
}

void GameObject::Update(float dt)
{
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, m_ObjTexture, NULL, &m_DstRect);
}
