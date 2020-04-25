#include "CastlevaniaScreen.h"

CastlevaniaScreen::CastlevaniaScreen( string filePath)
	: CScene(filePath) 
{
	this->gameMap = new GameMap(88, 12);
}

void CastlevaniaScreen::Load() {
	this->gameMap->LoadMap("textures/map2.txt");
}

void CastlevaniaScreen::Update() {

}

void CastlevaniaScreen::Render() {
	this->gameMap->DrawMap(0, 0);

}

void CastlevaniaScreen::Unload() {

}
