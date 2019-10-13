#include "Map.h"
#include "Game.h"
#include <fstream>
#include "Config.h"
#include <string>

Map::Map()
{
}

Map::~Map()
{

}

void Map::LoadMap(std::string path)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;
	char line[256] = "";
	char* word;
	char* next_token = NULL;
	mapFile.getline(line, 32);
	word = strtok_s(line, " ", &next_token);
	word = strtok_s(NULL, " ", &next_token);
	int sizeX = atoi(word);
	mapFile.getline(line, 32);
	word = strtok_s(line, " ", &next_token);
	word = strtok_s(NULL, " ", &next_token);
	int sizeY = atoi(word);
	mapFile.getline(line, 32);
	mapFile.getline(line, 32);
	mapFile.getline(line, 32);
	mapFile.getline(line, 32);
	int xPos, yPos;
	yPos = 0;

	while (mapFile.getline(line, 256))
	{
		xPos = 0;
		word = strtok_s(line, ",", &next_token);
		while (word != NULL)
		{
			int val = atoi(word);
			srcX = val % 10 * Config::TILE_SIZE;
			srcY = val / 10 * Config::TILE_SIZE;
			Game::AddTile(srcX, srcY, xPos * Config::TILE_SIZE * Config::MAP_SCALE, yPos * Config::TILE_SIZE * Config::MAP_SCALE);
			xPos++;
			word = strtok_s(NULL, ",", &next_token);
		}
		yPos++;
		if (yPos >= sizeY) break;
	}

	mapFile.close();
}
