#include "Grid.h"
#include "Simon.h"
#include "GameMap.h"
#include "Torch.h"
#include "Candle.h"
#include "ItemUpgrade.h"
#include "ItemDagger.h"
#include "Brick.h"
#include "Dagger.h"
#include "HidenObject.h"
#include "Ghost.h"
#include "CBoard.h"

Grid* Grid::__instance = NULL;

Grid* Grid::GetInstance()
{
	if (__instance == NULL)
		__instance = new Grid();
	return __instance;
}

void Grid::LoadObject(string file_path)
{
	//clear old data
	for (int i = 0; i < Row; i++)
	{
		delete[] cells[i];
	}
	SAFE_DELETE(cells);

	// New data
	Row = GameMap::GetInstance()->getRows();
	Col = GameMap::GetInstance()->getCols();
	CellW = GameMap::GetInstance()->getTileW();
	CellH = GameMap::GetInstance()->getTileH();

	cells = new vector<LPGAMEOBJECT>*[Row];
	for (int i = 0; i < Row; i++)
	{
		cells[i] = new vector<LPGAMEOBJECT>[Col];
		for (int j = 0; j < Col; j++)
		{
			cells[i][j].clear();
		}
	}

	ifstream inFile(file_path);

	int id, grid_x, grid_y, type, trend, id_item, nx, ny, object;
	float x, y, w, h;

	if (inFile)
	{
		while (inFile >> id >> grid_x >> grid_y >> type >> trend >> x >> y >> w >> h >> id_item >> object)
		{
			Insert(id, grid_x, grid_y, type, trend, x, y, w, h, id_item, object);
		}
		inFile.close();
	}
}

void Grid::Insert(int id, int grid_x, int grid_y, int type, int trend, float x, float y, float w, float h, int id_item, int object)
{
	CGameObject* obj = GetNewObject(type, trend, x, y, w, h, id_item, object);
	if (obj == NULL)
		return;

	obj->SetTrend(trend);
	obj->SetID(id);
	
	cells[grid_x][grid_y].push_back(obj);
}


CGameObject* Grid::GetNewObject(int type, int trend, int x, int y, int w, int h, int id_item, int object)
{
	switch (object)
	{
	case eType::ID_BRICK:
		return new Brick(x, y, id_item, type, w, h);

	case eType::ID_TORCH:
		return new Torch(x, y, id_item);

	case eType::ID_CANDLE:
		return new Candle(x, y, id_item);

	case eType::ID_HIDDEN:
		return new CHidenObject(x, y, w, h, type, trend);

	case eType::GHOST: 
		return new Ghost(x, y, id_item);

	default:
		return NULL;
	}
}


void Grid::GetListObject(vector<LPGAMEOBJECT>&ListObj, float cam_x, float cam_y)
{

	ListObj.clear();

	unordered_map<int, LPGAMEOBJECT> mapObject;

	int bottom = (int)((cam_y + SCREEN_HEIGHT) / CellH);
	int top = (int)(cam_y / CellH);

	int left = (int)(cam_x / CellW);
	//if (left > 0) left--;
	int right = (int)((cam_x + SCREEN_WIDTH) / CellW);
	//right++;

	for (int i = top; i < bottom && i < Row; i++)
	{
		for (int j = left; j < right && j < Col; j++)
		{
			for (UINT k = 0; k < cells[i][j].size(); k++)
			{
				if (cells[i][j].at(k)->GetState() != TORCH_STATE_ITEM_NOT_EXSIST || cells[i][j].at(k)->GetState() != CANDLE_STATE_ITEM_NOT_EXSIST || dynamic_cast<Enemy*>(cells[i][j].at(k))) // còn tồn tại || enemy
				{
					if (mapObject.find(cells[i][j].at(k)->GetID()) == mapObject.end()) // chưa có trong map
						mapObject[cells[i][j].at(k)->GetID()] = cells[i][j].at(k);
				}
			}
		}
	}

	for (auto& x : mapObject)
	{
		ListObj.push_back(x.second);
	}
}
