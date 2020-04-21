#pragma once
#include <string>
#include <vector>
#include "Textures.h"
#include "Game.h"

#define SCREEN_WIDTH 520
#define SCREEN_HEIGHT 460
#define ID_TEX_MAP1 4

using namespace std;


class Map
{
public:
	Map();
	~Map();

	int scene;

	int width;
	int height;
	int col;
	int row;
	int numCol;
	int numRow;
	int listTile[100][100];

	RECT GetSourceRect(int index);
	void LoadMap(const char* filepath);
	void DrawMap();

};

