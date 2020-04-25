#pragma once

#include "Scence.h"
#include "Map.h"

class CastlevaniaScreen: public CScene
{
public:
	CastlevaniaScreen(int id, LPCWSTR filePath);

private:
	Map *mapOfScreen;

protected:	
	virtual void Load();
	virtual void Update();
	virtual void Render();
	virtual void Unload();
};

