#ifndef __GAMEMAP_H__

#define __GAMEMAP_H__


#include <string>
#include <vector>
#include "Textures.h"
#include "Define.h"
#include "Sprites.h"

//#define ID_TEX_MAP1 4
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
	int id, cellW, cellH;
	
	// cell type
	int cellTypes[200][200];

public:
	void setId(int _id) { this->id = _id; }
	void LoadMap(int _id, string filepath);
	void DrawMap();
	int getRows() { return numRows; }
	int getCols() { return numCols; }
	int getTileW() { return cellW; }
	int getTileH() { return cellH; }

private:
	int getTitle(int x, int y);
};
#endif // !__GAMEMAP_H__

