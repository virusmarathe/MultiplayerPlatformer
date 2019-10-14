#include "Map.h"
#include "Game.h"
#include <fstream>
#include "Config.h"
#include <string>
#include "ECS/ECS.h"
#include "ECS/Components.h"

extern EntityManager manager;

Map::Map(const char* path) : tileMapPath(path), width(0), height(0)
{
}

Map::~Map()
{

}

void Map::LoadMap(std::string path)
{
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
	int xPos;
	int mapMultiplier = Config::TILE_SIZE * Config::MAP_SCALE;
	width = sizeX;
	height = sizeY;

	for (int yPos = 0; yPos < sizeY; yPos++)
	{
		mapFile.getline(line, 256);
		xPos = 0;
		word = strtok_s(line, ",", &next_token);
		while (word != NULL)
		{
			int val = atoi(word);
			srcX = val % 10 * Config::TILE_SIZE;
			srcY = val / 10 * Config::TILE_SIZE;
			AddTile(srcX, srcY, xPos * mapMultiplier, yPos * mapMultiplier);
			xPos++;
			word = strtok_s(NULL, ",", &next_token);
		}
	}
	mapFile.getline(line, 32);
	mapFile.getline(line, 32);
	for (int yPos = 0; yPos < sizeY; yPos++)
	{
		mapFile.getline(line, 256);
		xPos = 0;
		word = strtok_s(line, ",", &next_token);
		while (word != NULL)
		{
			int val = atoi(word);
			if (val != -1)
			{
				auto& col(manager.addEntity());
				col.addComponent<TransformComponent>(xPos * mapMultiplier, yPos * mapMultiplier, Config::MAP_SCALE);
				col.addComponent<ColliderComponent>("terrain", 0, 0, Config::TILE_SIZE, Config::TILE_SIZE);
				col.addGroup(Game::LAYER_COLLIDERS);
			}
			xPos++;
			word = strtok_s(NULL, ",", &next_token);
		}
	}

	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileMapPath);
	tile.addGroup(Game::LAYER_MAP);
}
