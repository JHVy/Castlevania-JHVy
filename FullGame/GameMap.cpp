#include "GameMap.h"
#include <stdio.h>
#include <stdlib.h>
#include "fstream"
#include "Utils.h"

GameMap::GameMap() {
	this->numCols = 0;
	this->numRows = 0;
	this->id = 0;
}

GameMap::~GameMap()
{
}

void GameMap::LoadMap(int _id, string filepath) {
	ifstream inFile;
	inFile.open(filepath);

	this->id = _id;
	inFile >> numRows;
	inFile >> numCols;
	inFile >> cellW;
	inFile >> cellH;

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			inFile >> cellTypes[i][j];
		}
	}

	int game_stage = _id;
	//Mapi
	string sPath = "Res\\maps\\map" + to_string(game_stage) + ".png";
	CTextures::GetInstance()->Add(game_stage, ToLPCWSTR(sPath), D3DCOLOR_XRGB(255, 0, 255));
	int index = 0;
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			CSprites::GetInstance()->Add(index++, j * cellW, i * cellH, (j + 1) * cellW, (i + 1) * cellH, 
				CTextures::GetInstance()->Get(game_stage));
		}
	}


}

int GameMap::getTitle(int x, int y)
{
	return cellTypes[x][y];
}

void GameMap::DrawMap() {
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			float posX = j * cellW;
			float posY = i * cellH + SCREEN_PADING_TOP;

			if (posX < 0 || posY < 0) continue;
			
			if (CSprites::GetInstance()->Get(getTitle(i, j)) != NULL) 
				CSprites::GetInstance()->Get(getTitle(i, j))->Draw(posX, posY);
		}
	}
}



