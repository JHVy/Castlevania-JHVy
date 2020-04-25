#pragma once
#include <string>
#include <vector>
#include "Textures.h"
#include "Game.h"

#define SCREEN_WIDTH 520
#define SCREEN_HEIGHT 460
#define ID_TEX_MAP1 4

using namespace std;

const int maxHeight = 60;

class Map
{
public:
	Map();
	Map(int mapType);
	~Map();


private:
	int numRows, numcols; 
	int cellHeight, cellWidth;
	
	// cell type
	int cellTypes[maxHeight][maxHeight];

public:
	void LoadMap(const char* filepath);
	void DrawMap();

};

