#include "CastlevaniaScreen.h"

CastlevaniaScreen::CastlevaniaScreen( string filePath)
	: CScene(filePath) 
{
	// load resource
	LoadSpriteResource();

	// init 
	this->gameMap = new GameMap(2);
	this->simon = new Simon();
}

void CastlevaniaScreen::Load() {
	
	//this->gameMap->setId(2);
	//this->gameMap->LoadMap("textures/map2.txt", 88, 12);

	this->gameMap->setId(1);
	this->gameMap->LoadMap("textures/map.txt", 24, 12);

	this->simon->SetPosition(200, 300);
	
}

void CastlevaniaScreen::Update() {

}

void CastlevaniaScreen::Render() {
	this->gameMap->DrawMap(0, 0);
	this->simon->Render();

	//float x, y;
	//this->simon->GetPosition(x, y);
	//this->simon->SetPosition(x + 1.5, y);

}

void CastlevaniaScreen::Unload() {

}
