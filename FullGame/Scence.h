#pragma once

#include <cstring>
#include <string>
#include <d3dx9.h>
#include "KeyEventHandler.h"

using namespace std;

class CScene
{
protected:
	CKeyEventHandler * key_handler;
	string sceneFilePath;

public: 
	CScene(string filepath);

	CKeyEventHandler * GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0; 
};
typedef CScene * LPSCENE;
