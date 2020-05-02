#ifndef __CASTLEVANIASCREEN_H__

#define __CASTLEVANIASCREEN_H__

#include "GameMap.h"
#include <string>
#include "KeyEventHandler.h"
#include "Textures.h"
#include "Define.h"
#include "Simon.h"
#include "Loader.h"
#include "Camera.h"
#include "Game.h"

class CGame;

class CastlevaniaScreen
{
protected:
	GameMap * gameMap;
	string path;

	float screen_size_x, screen_size_y;
	
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

private:
	void UpdateCamera();
};

#endif // !__CASTLEVANIASCREEN_H__

