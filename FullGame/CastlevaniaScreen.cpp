#include "CastlevaniaScreen.h"

CastlevaniaScreen::CastlevaniaScreen( string filePath) 
{
	this->path = filePath;
	CastlevaniaScreen();
}

CastlevaniaScreen::CastlevaniaScreen() {
	// load resource
	LoadSpriteResource();

	// init 
	this->gameMap = new GameMap(2);
	this->simon = new Simon();
}

void CastlevaniaScreen::Load() {

	this->gameMap->setId(1);
	this->gameMap->LoadMap("textures/map.txt", 24, 12);

	this->simon->SetPosition(200, 300);
	
}

void CastlevaniaScreen::Update(DWORD dt) {
	this->simon->Update(dt, NULL);
}

void CastlevaniaScreen::Render() {
	this->gameMap->DrawMap(200, 0);
	this->simon->Render();

	//float x, y;

}

void CastlevaniaScreen::Unload() {

}
