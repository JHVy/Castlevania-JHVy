#include "GameMap.h"
#include <stdio.h>
#include <stdlib.h>
#include "fstream"


GameMap::GameMap(int _id) {
	this->numCols = 88;
	this->numRows = 12;
	this->id = _id;
}

GameMap::~GameMap()
{
}

void GameMap::LoadMap(string filepath, int _numCols, int _numRows) {
	ifstream inFile;
	inFile.open(filepath);


	for (int i = 0; i < _numRows; i++)
	{
		for (int j = 0; j < _numCols; j++)
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
			float posY = i * TILE_SIZE + 40;

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



