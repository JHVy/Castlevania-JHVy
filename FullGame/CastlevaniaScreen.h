#ifndef __CASTLEVANIASCREEN_H__

#define __CASTLEVANIASCREEN_H__

#include "GameMap.h"
#include "Scence.h"
#include <string>
#include "KeyEventHandler.h"
#include "Textures.h"
#include "Define.h"

class CastlevaniaScreen: public CScene
{
	GameMap * gameMap;
public:
	CastlevaniaScreen(string filePath);


protected:	
	virtual void Load();
	virtual void Update();
	virtual void Render();
	virtual void Unload();
};

#endif // !__CASTLEVANIASCREEN_H__

