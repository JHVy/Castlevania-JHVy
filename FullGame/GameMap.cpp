#include "GameMap.h"
#include <stdio.h>
#include <stdlib.h>
#include "fstream"


GameMap::GameMap() {
	this->numCols = 88;
	this->numRows = 12;
}

GameMap::GameMap(int _numCols, int _numRows)
{
	this->numCols = _numCols;
	this->numRows = _numRows;
}


GameMap::~GameMap()
{
}

void GameMap::LoadMap(string filepath) {
	ifstream inFile;
	inFile.open(filepath);


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
	return this->cellTypes[x][y];
}


void GameMap::DrawMap(float cam_x, float cam_y) {
	if (cam_y == 0)
	{
		for (int i = (int)cam_y / TILE_SIZE; i < (int)(cam_y + SCREEN_HEIGHT) / TILE_SIZE + 2; i++)
		{
			for (int j = (int)cam_x / TILE_SIZE; j < (int)(cam_x + SCREEN_WIDTH) / TILE_SIZE + 3; j++)
			{
				if (!(i < 0 || j >= numCols))
					CSprites::GetInstance()->Get(getTitle(i, j))->Draw(TILE_SIZE * j, TILE_SIZE * i + 40);
			}
		}
	}
	else
	{
		for (int i = (int)cam_y / TILE_SIZE; i < 12; i++)
		{
			for (int j = (int)cam_x / 64; j < (int)(cam_x + SCREEN_WIDTH) / TILE_SIZE + 3; j++)
			{
				if (!(i < 0 || j >= numCols))
				{
					CSprites::GetInstance()->Get(getTitle(i, j))->Draw(TILE_SIZE * j, TILE_SIZE * i + 80);
				}

			}
		}
	}
	/*if (_scene == 0)
	{
		for (int i = (int)cam_x / TILE_SIZE; i <= (int)(cam_x + SCREEN_WIDTH) / BRICK_SIZE; i++)
			CSprites::GetInstance()->Get(9999)->Draw(i * BRICK_SIZE, 360);
	}*/
}

//RECT Map::GetSourceRect(int _index)
//{
//	RECT srect;
//
//	srect.left = (_index % 24) * 32;
//	srect.top = (_index / 24) * 32;
//	srect.right = srect.left + 32;
//	srect.bottom = srect.top + 32;
//
//	return srect;
//}
//
//void Map::LoadMap(const char *filepath)
//{
//
//	FILE* pFile;
//	pFile = fopen(filepath, "r");
//	
//	/*errno_t err = fopen_s(&pFile, filepath, "r");
//
//	if (err)
//	{
//		printf_s("Can't open file!");
//	}*/
//
//	
//	//switch(scene)
//	//{
//	//case 0:
//	//	filepath = "textures\\Scene1.csv";
//	//	break;
//	//case 1:
//	//	//load scene 2 ...
//	//	break;
//	//}
//
//	fscanf_s(pFile, "%d %d %d %d %d %d", &row, &col, &numRow, &numCol, &width, &height);
//
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			fscanf_s(pFile, "%d", &listTile[i][j]);
//		}
//	}
//
//
//	fclose(pFile);
//}
//
//void Map::DrawMap()
//{
//	
//	int rowCam = CGame::GetInstance()->GetCamPos().y/ height;
//	int colCam = CGame::GetInstance()->GetCamPos().x / width;
//
//	int x = (int)CGame::GetInstance()->GetCamPos().x % width;
//	int y = (int)CGame::GetInstance()->GetCamPos().y % height;
//
//	for (int i = 0; i < SCREEN_HEIGHT / height; i++)
//	{
//		for (int j = 0; j < SCREEN_WIDTH / width + 1; j++)
//		{
//			RECT rect = GetSourceRect(listTile[i + rowCam][j + colCam]);
//			CGame::GetInstance()->Draw(j * width - x, i * height - y + 40, CTextures::GetInstance()->Get(ID_TEX_MAP1), rect.left, rect.top, rect.right, rect.bottom);
//		}
//	}
//}


