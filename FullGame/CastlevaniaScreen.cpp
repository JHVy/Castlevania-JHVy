#include "CastlevaniaScreen.h"

CastlevaniaScreen::CastlevaniaScreen( string filePath)
	: CScene(filePath) 
{
	this->gameMap = new GameMap(2);
	this->simon = new Simon();
}

void CastlevaniaScreen::Load() {
	
	//this->gameMap->setId(2);
	//this->gameMap->LoadMap("textures/map2.txt", 88, 12);

	this->gameMap->setId(1);
	this->gameMap->LoadMap("textures/map.txt", 24, 12);

	this->simon->SetPosition(100, 0);
	
}

void CastlevaniaScreen::Update() {

}

void CastlevaniaScreen::Render() {
	this->gameMap->DrawMap(0, 0);
	this->simon->Render();

}

void CastlevaniaScreen::Unload() {

}
