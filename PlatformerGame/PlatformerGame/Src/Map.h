#pragma once
#include "Game.h"

class Map
{
public:
	Map(const char* path);
	~Map();

	void LoadMap(std::string path);
	void AddTile(int srcX, int srcY, int xpos, int ypos);

	int width;
	int height;

private:
	const char* tileMapPath;
};

