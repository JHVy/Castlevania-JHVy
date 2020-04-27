#ifndef __CASTLEVANIASCREEN_H__

#define __CASTLEVANIASCREEN_H__

#include "GameMap.h"
#include <string>
#include "KeyEventHandler.h"
#include "Textures.h"
#include "Define.h"
#include "Simon.h"
#include "Loader.h"

class CastlevaniaScreen
{
protected:
	GameMap * gameMap;
	
	string path;

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
};

#endif // !__CASTLEVANIASCREEN_H__

