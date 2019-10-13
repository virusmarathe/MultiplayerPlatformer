#include "TextureManager.h"

std::map<const char*, SDL_Texture*> TextureManager::m_CachedTex;

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	SDL_Texture* tex;
	if (m_CachedTex.find(fileName) != m_CachedTex.end())
	{
		tex = m_CachedTex[fileName];
	}
	else
	{
		tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
		m_CachedTex[fileName] = tex;
	}

	SDL_FreeSurface(tmpSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dst, NULL, NULL, flip);
}
