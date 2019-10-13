#include "Map.h"
#include "Game.h"
#include <fstream>
#include "Config.h"

Map::Map()
{
}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			// example if next tile index is "21", 2 is y index, 1 is x index
			// could refactor to read in based on commas, and then calculate the position in tilemap based on width
			mapFile.get(c); 
			srcY = atoi(&c) * Config::TILE_SIZE;
			mapFile.get(c);
			srcX = atoi(&c) * Config::TILE_SIZE;
			Game::AddTile(srcX, srcY, x * Config::TILE_SIZE * Config::MAP_SCALE, y * Config::TILE_SIZE * Config::MAP_SCALE);
			mapFile.ignore();
		}
	}

	mapFile.close();
}
