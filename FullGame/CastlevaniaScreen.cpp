#include "CastlevaniaScreen.h"
#include "GameConfig.h"

CastlevaniaScreen::CastlevaniaScreen( string filePath) 
{
	this->path = filePath;
	CastlevaniaScreen();
}

CastlevaniaScreen::CastlevaniaScreen() {
	// init 
	this->gameMap = new GameMap();
	this->simon = Simon::GetInstance();

	this->board = new CBoard();
}

CGameObject* CastlevaniaScreen::GetNewObject(int type, int trend, int x, int y, int w, int h, int id_item, int object)
{
	CGameObject* objRet = NULL;
	switch (object)
	{
	case eType::ID_BRICK:
		objRet = new Brick(x, y, id_item, type, w, h);
		return objRet;

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

void CastlevaniaScreen::LoadObject(string file_path) 
{
	items.clear();

	ifstream inFile(file_path);

	int id, grid_x, grid_y, type, trend, id_item, nx, ny, object;
	float x, y, w, h;

	if (inFile)
	{
		while (inFile >> id >> grid_x >> grid_y >> type >> trend >> x >> y >> w >> h >> id_item >> object)
		{
			CGameObject* obj = GetNewObject(type, trend, x, y, w, h, id_item, object);
			if (obj != NULL)
				items.push_back(obj);
		}
		inFile.close();
	}

	this->simon->SetListObject(&items);
}

void CastlevaniaScreen::Load() {
	int gameLevel = GameConfig::GetInstance()->CurrentLevel;
	this->simon->ResetLevel(gameLevel);
	string sScreenID = to_string(gameLevel);

	this->gameMap->LoadMap(gameLevel, "Res/maps/map" + sScreenID + ".txt");
	//this->gameMap->LoadMap(2, "Res/maps/map6.txt");

	this->screen_size_x = this->gameMap->getCols() * this->gameMap->getTileW();
	this->screen_size_y = this->gameMap->getRows() * this->gameMap->getTileH();

	this->LoadObject("Res/maps/objects_" + sScreenID + ".txt");
	//this->LoadObject("Res/maps/objects_6.txt");
}

void CastlevaniaScreen::Update(DWORD dt) {

	this->simon->Update(dt, &items);

	float simon_x, simon_y;
	this->simon->GetPosition(simon_x, simon_y);
	if (simon_x >= this->screen_size_x) 
	{
		simon_x = this->screen_size_x;
		this->simon->SetPosition(simon_x, simon_y);
	}

	// update
	if (!items.empty()) 
	{
		for (int i = 0; i < items.size(); i++) {
			items[i]->Update(dt, &items);
		}
	}

	this->UpdateCamera();
	board->Update(dt);
}

void CastlevaniaScreen::UpdateCamera() {
	float simon_x, simon_y;
	this->simon->GetPosition(simon_x, simon_y);

	float cam_x = 0, cam_y = 0;

	float kc_x = SCREEN_WIDTH / 2;
	float kc_y = SCREEN_HEIGHT / 2;

	cam_x = simon_x - kc_x;
	//cam_y = simon_y - kc_y;

	if (cam_x + SCREEN_WIDTH > this->screen_size_x)
		cam_x = this->screen_size_x  - SCREEN_WIDTH;
	if (cam_x < 0) cam_x = 0;

	//DebugOut(L"[DEBUG] Cal postion camera : (%f, %f) - (%f, %f) - (%f, %f) !\n", screen_x, screen_y, mainObject_x, mainObject_y, cam_x, cam_y);

	if (cam_y < 0) cam_y = 0;
	
	CGame::GetInstance()->setCamera(cam_x, cam_y);
}

void CastlevaniaScreen::Render() {
	// render
	this->gameMap->DrawMap();

	if (!items.empty()) 
	{
		for (int i = 0; i < items.size(); i++) 
		{
			items[i]->Render();
		}
	}

	this->simon->Render();
	this->board->Render();
}

void CastlevaniaScreen::Unload() {

}
