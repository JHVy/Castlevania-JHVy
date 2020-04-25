#ifndef __GAMEMAP_H__

#define __GAMEMAP_H__


#include <string>
#include <vector>
#include "Textures.h"
#include "Define.h"
#include "Sprites.h"

#define ID_TEX_MAP1 4
#define TILE_SIZE 64
#define BRICK_SIZE 32

using namespace std;

class GameMap
{
public:
	GameMap();
	~GameMap();


private:
	int numRows, numCols; 
	
	// cell type
	int cellTypes[200][200];

public:
	void LoadMap(string filepath, int _numCols, int _numRows);
	void DrawMap(float cam_x, float cam_y);

private:
	int getTitle(int x, int y);
};
#endif // !__GAMEMAP_H__

