#include "GameMap.h"
#include <stdio.h>
#include <stdlib.h>


GameMap::GameMap() {

}

GameMap::GameMap(int mapType)
{
	CTextures* textures = CTextures::GetInstance();
	textures->Add(ID_TEX_MAP1, L"textures\\Level1Entrance.png", D3DCOLOR_XRGB(255, 0, 255));
}


GameMap::~GameMap()
{
}

void GameMap::LoadMap(string filepath) {

}

void GameMap::DrawMap() {

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


