#include "Map.h"
#include "TextureManager.h"

int lvl1[20][25] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
	{0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map()
{
	dirt = TextureManager::LoadTexture("assets/dirt.png");
	grass = TextureManager::LoadTexture("assets/grass.png");
	water = TextureManager::LoadTexture("assets/water.png");

	src.x = src.y = 0;
	src.w = dst.w = 32;
	src.h = dst.h = 32;

	LoadMap(lvl1);
}

Map::~Map()
{
	SDL_DestroyTexture(dirt);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(water);
}

void Map::LoadMap(int arr[20][25])
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			map[i][j] = arr[i][j];
		}
	}
}

void Map::DrawMap()
{
	int type = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			type = map[i][j];
			dst.x = j * 32;
			dst.y = i * 32;
			switch (type)
			{
				case 0:
					TextureManager::Draw(water, src, dst);
					break;
				case 1:
					TextureManager::Draw(grass, src, dst);
					break;
				case 2:
					TextureManager::Draw(dirt, src, dst);
					break;
			}
		}
	}
}