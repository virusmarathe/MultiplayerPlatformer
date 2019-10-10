#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, int xpos, int ypos, int scale = 1);
	~GameObject();

	void Update(float dt);
	void Render();

private:
	int mi_xPos;
	int mi_yPos;

	SDL_Texture* m_ObjTexture;
	SDL_Rect m_DstRect;
};

