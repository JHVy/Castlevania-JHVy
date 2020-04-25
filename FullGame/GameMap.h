#ifndef __GAMEMAP_H__

#define __GAMEMAP_H__


#include <string>
#include <vector>
#include "Textures.h"
#include "Define.h"

#define SCREEN_WIDTH 520
#define SCREEN_HEIGHT 460
#define ID_TEX_MAP1 4

using namespace std;

const int maxHeight = 60;

class GameMap
{
public:
	GameMap();
	GameMap(int mapType);
	~GameMap();


private:
	int numRows, numcols; 
	int cellHeight, cellWidth;
	
	// cell type
	int cellTypes[maxHeight][maxHeight];

public:
	void LoadMap(string filepath);
	void DrawMap();

};
#endif // !__GAMEMAP_H__

