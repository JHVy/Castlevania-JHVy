#pragma once
#include <vector>
#include "GameObject.h"
#include "Game.h"
#include "Define.h"

#define GRID_CELL_HEIGHT SCREEN_HEIGHT
#define GRID_CELL_WIDTH SCREEN_WIDTH

using namespace std;

class Grid
{
	static Grid* __instance;

	vector<LPGAMEOBJECT>** cells;
public:
	static bool IsOutOfCamera(float cam_x, float cam_y, LPGAMEOBJECT obj);
	static Grid* GetInstance();

	int Row, Col, CellW, CellH;
	void LoadObject(string file_path);
	void Insert(int id, int grid_x, int grid_y, int type, int trend, float x, float y, float w, float h, int id_item, int object);
	CGameObject* GetNewObject(int type, int trend, int x, int y, int w, int h, int id_item, int object);
	void GetListObject(vector<LPGAMEOBJECT>& ListObj, float cam_x, float cam_y);
};

