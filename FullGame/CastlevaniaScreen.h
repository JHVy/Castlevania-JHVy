#ifndef __CASTLEVANIASCREEN_H__

#define __CASTLEVANIASCREEN_H__

#include "GameMap.h"
#include <string>
#include "KeyEventHandler.h"
#include "Textures.h"
#include "Define.h"
#include "Simon.h"
#include "Loader.h"
#include "Game.h"
#include "CBoard.h"

#include "ItemHeart.h"
#include "Torch.h"
#include "Candle.h"
#include "Ghost.h"
#include "HidenObject.h"
#include "Brick.h"

#include "Grid.h"

class CGame;
class Simon;
class CBoard;

class CastlevaniaScreen
{
protected:
	GameMap * gameMap;
	string path;

	CBoard * board;

	Grid* grid;

	float screen_size_x, screen_size_y;
	vector<CGameObject*> items;

	
public:
	Simon* simon;

public:
	CastlevaniaScreen(string filePath);
	CastlevaniaScreen();

public:	
	virtual void Load();
	void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	vector<CGameObject*> getListObject() {
		return this->items;
	}

private:
	void UpdateCamera();
	//void LoadObject(string file_path); //
	//CGameObject* GetNewObject(int type, int trend, int x, int y, int w, int h, int id_item, int object);
};

#endif // !__CASTLEVANIASCREEN_H__

