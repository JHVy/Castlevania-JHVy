#include "CastlevaniaScreen.h"
#include "GameConfig.h"

CastlevaniaScreen::CastlevaniaScreen( string filePath) 
{
	this->path = filePath;
	CastlevaniaScreen();
}

CastlevaniaScreen::CastlevaniaScreen() {
	// init 
	this->gameMap = GameMap::GetInstance();
	this->simon = Simon::GetInstance();

	this->board = CBoard::GetInstance();
	this->grid = Grid::GetInstance();
}



void CastlevaniaScreen::Load() {
	int gameLevel = GameConfig::GetInstance()->CurrentLevel;
	this->simon->ResetLevel(gameLevel);
	string sScreenID = to_string(gameLevel);

	this->gameMap->LoadMap(gameLevel, "Res/maps/map" + sScreenID + ".txt");

	this->screen_size_x = this->gameMap->getCols() * this->gameMap->getTileW();
	this->screen_size_y = this->gameMap->getRows() * this->gameMap->getTileH();

	grid->LoadObject("Res/maps/objects_" + sScreenID + ".txt");
}

void CastlevaniaScreen::Update(DWORD dt) {
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamera(cam_x, cam_y);
	
	//update list object cho grid
	items.clear();
	grid->GetListObject(items, cam_x, cam_y);
	simon->SetListObject(&items);

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

	if (simon->GetCurrentWeapon() != NULL)
	{
		simon->GetCurrentWeapon()->Update(dt, &items);
	}

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

	if (simon->GetCurrentWeapon() != NULL)
	{
		simon->GetCurrentWeapon()->Render();
	}

	this->simon->Render();
	this->board->Render();
	
}

void CastlevaniaScreen::Unload() {

}
