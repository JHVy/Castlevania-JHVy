#include "CastlevaniaScreen.h"

CastlevaniaScreen::CastlevaniaScreen( string filePath)
	: CScene(filePath) 
{
	this->gameMap = new GameMap(2);
}

void CastlevaniaScreen::Load() {
	
	//this->gameMap->setId(2);
	//this->gameMap->LoadMap("textures/map2.txt", 88, 12);

	this->gameMap->setId(1);
	this->gameMap->LoadMap("textures/map.txt", 24, 12);
	
}

void CastlevaniaScreen::Update() {

}

void CastlevaniaScreen::Render() {
	this->gameMap->DrawMap(0, 0);

}

void CastlevaniaScreen::Unload() {

}
