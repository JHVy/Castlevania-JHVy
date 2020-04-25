#ifndef __GAMEMAP_H__

#define __GAMEMAP_H__


#include <string>
#include <vector>
#include "Textures.h"
#include "Define.h"
#include "Sprites.h"

#define SCREEN_WIDTH 520
#define SCREEN_HEIGHT 460
#define ID_TEX_MAP1 4
#define TILE_SIZE 64

using namespace std;

const int maxHeight = 200;

class GameMap
{
public:
	GameMap();
	GameMap(int _numCols, int _numRows);
	~GameMap();


private:
	int numRows, numCols; 
	
	// cell type
	int cellTypes[maxHeight][maxHeight];

public:
	void LoadMap(string filepath);
	void DrawMap(float cam_x, float cam_y);

private:
	int getTitle(int x, int y);
};
#endif // !__GAMEMAP_H__

