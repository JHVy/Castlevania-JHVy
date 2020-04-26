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
	GameMap(int _id);
	~GameMap();


private:
	int numRows, numCols; 
	int id;
	
	// cell type
	int cellTypes[200][200];

public:
	void setId(int _id) { this->id = _id; }
	void LoadMap(string filepath, int _numCols, int _numRows);
	void DrawMap(float cam_x, float cam_y);

private:
	int getTitle(int x, int y);
};
#endif // !__GAMEMAP_H__

