#include "GameMap.h"
#include <stdio.h>
#include <stdlib.h>
#include "fstream"

GameMap::GameMap() {
	this->numCols = 0;
	this->numRows = 0;
	this->id = 0;
}

GameMap::~GameMap()
{
}

void GameMap::LoadMap(int _id, string filepath, int _numCols, int _numRows) {
	ifstream inFile;
	inFile.open(filepath);

	this->id = _id;
	this->numRows = _numRows;
	this->numCols = _numCols;

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			inFile >> cellTypes[i][j];
		}
	}
}

int GameMap::getTitle(int x, int y)
{
	return cellTypes[x][y];
}

CSprite temp;
void GameMap::DrawMap() {
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			float posX = j * TILE_SIZE;
			float posY = i * TILE_SIZE + SCREEN_PADING_TOP;

			if (posX < 0 || posY < 0) continue;
			
			if (CSprites::GetInstance()->Get(getTitle(i, j)) != NULL) 
				CSprites::GetInstance()->Get(getTitle(i, j))->Draw(posX, posY);
			
				
		}
	}


	if (this->id == 1)
	{
		for (int j = 0; j < numCols*2; j++) {
			int i = 5;

			float posX = j * BRICK_SIZE;
			float posY = i * TILE_SIZE + 40;

			if (posX >= 0 && posY >= 0)
				CSprites::GetInstance()->Get(9999)->Draw(posX, posY);
		}
	}
}



