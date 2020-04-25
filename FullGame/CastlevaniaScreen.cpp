#include "CastlevaniaScreen.h"

CastlevaniaScreen::CastlevaniaScreen( string filePath)
	: CScene(filePath) 
{
	this->gameMap = new GameMap();
	
}

void CastlevaniaScreen::Load() {
	
	// this->gameMap->LoadMap("textures/map2.txt", 88, 12);
	this->gameMap->LoadMap("textures/map.txt", 24, 12);
	
}

void CastlevaniaScreen::Update() {

}

void CastlevaniaScreen::Render() {
	this->gameMap->DrawMap(0, 0);

}

void CastlevaniaScreen::Unload() {

}
