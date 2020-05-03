#include "CastlevaniaScreen.h"

CastlevaniaScreen::CastlevaniaScreen( string filePath) 
{
	this->path = filePath;
	CastlevaniaScreen();
}

CastlevaniaScreen::CastlevaniaScreen() {
	

	// init 
	this->gameMap = new GameMap(2);
	this->simon = new Simon();
}

void CastlevaniaScreen::Load() {

	this->gameMap->setId(1);
	this->gameMap->LoadMap("textures/map.txt", 24, 12);

	this->screen_size_x = 23 * 64 - 15;
	this->screen_size_y = 12 * 64;

	float start_simon_x = 60, start_simon_y = 150;
	this->simon->SetPosition(start_simon_x, start_simon_y);

	items.clear();
	items.push_back(new Item_Heart(100, 270));
	items.push_back(new Item_Heart(400, 270));
}

void CastlevaniaScreen::Update(DWORD dt) {
	this->simon->Update(dt, NULL);

	float simon_x, simon_y;
	this->simon->GetPosition(simon_x, simon_y);
	if (simon_x > this->screen_size_x) {
		simon_x = this->screen_size_x;
		this->simon->SetPosition(simon_x, simon_y);
	}

	// update
	if (!items.empty()) {
		for (int i = 0; i < items.size(); i++) {
			items[i]->Update(dt, NULL);
		}
	}

	this->UpdateCamera();
}

void CastlevaniaScreen::UpdateCamera() {
	float simon_x, simon_y;
	this->simon->GetPosition(simon_x, simon_y);

	float cam_x = 0, cam_y = 0;

	float kc_x = SCREEN_WIDTH / 2;
	float kc_y = SCREEN_HEIGHT / 2;

	cam_x = simon_x - kc_x;
	//cam_y = simon_y - kc_y;

	if (cam_x + SCREEN_WIDTH >= this->screen_size_x)
		cam_x = this->screen_size_x - SCREEN_WIDTH;
	if (cam_x < 0) cam_x = 0;

	//DebugOut(L"[DEBUG] Cal postion camera : (%f, %f) - (%f, %f) - (%f, %f) !\n", screen_x, screen_y, mainObject_x, mainObject_y, cam_x, cam_y);

	if (cam_y < 0) cam_y = 0;
	
	CGame::GetInstance()->setCamera(cam_x, cam_y);
}

void CastlevaniaScreen::Render() {
	// render
	this->gameMap->DrawMap();

	//this->gameMap->DrawMap(450, 0);
	this->simon->Render();

	if (!items.empty()) {
		for (int i = 0; i < items.size(); i++) {
			items[i]->Render();
		}
	}
}

void CastlevaniaScreen::Unload() {

}
