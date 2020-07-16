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

bool Grid::IsOutOfCamera(float cam_x, float cam_y, LPGAMEOBJECT obj)
{
	RECT rectThis, rect1;

	// CAM
	float l = cam_x, t = cam_y, r = cam_x + SCREEN_WIDTH-100, b = cam_y + SCREEN_HEIGHT;
	rectThis.left = (int)l;
	rectThis.top = (int)t;
	rectThis.right = (int)r;
	rectThis.bottom = (int)b;

	//obj
	float l1, t1, r1, b1;
	obj->GetBoundingBox(l1, t1, r1, b1);
	rect1.left = (int)l1;
	rect1.top = (int)t1;
	rect1.right = (int)r1;
	rect1.bottom = (int)b1;

	return !CGame::GetInstance()->isCollision(rectThis, rect1);
}

void Grid::GetListObject(vector<LPGAMEOBJECT>&ListObj, float cam_x, float cam_y)
{

	ListObj.clear();

	unordered_map<int, LPGAMEOBJECT> mapObject;

	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			for (UINT k = 0; k < cells[i][j].size(); k++)
			{
				LPGAMEOBJECT pObj = cells[i][j].at(k);
				if (!Grid::IsOutOfCamera(cam_x, cam_y, pObj))	// thuoc man hinh camera dang hien thi
				{
					if (mapObject.find(pObj->GetID()) == mapObject.end()) // chưa có trong map
						mapObject[pObj->GetID()] = pObj;
				}
			}
		}
	}

	for (auto& x : mapObject)
	{
		ListObj.push_back(x.second);
	}
}
