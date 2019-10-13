#pragma once

#include "Game.h"
#include <map>

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip);

	static std::map<const char *, SDL_Texture*> m_CachedTex;
};

