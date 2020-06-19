#pragma once

#include <unordered_map>

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>


#define DIRECTINPUT_VERSION 0x0800
#define MAX_LEVEL			5
#include <dinput.h>

#include "CastlevaniaScreen.h"
#include "CastkeKeyEventHandler.h"

using namespace std;

class CastkeKeyEventHandler;
class CastlevaniaScreen;

class CGame
{
	static CGame * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;		
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	CastkeKeyEventHandler* keyHandler;

	int screen_width;
	int screen_height; 

	unordered_map<int, CastlevaniaScreen*> screens;
	int current_scene; 

	float cam_x = 0, cam_y = 0;

public:
	void display();
	void Update(DWORD dt);

public:
	void InitKeyboard();
	void SetKeyHandler(CastkeKeyEventHandler* handler) { keyHandler = handler; }
	void Init(HWND hWnd);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
	void DrawFlipX(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha =255);

	void ProcessKeyboard();

	void Load();
	CastlevaniaScreen* GetCurrentScene() { return this->screens[current_scene]; }
	void SwitchScene(int scene_id);

	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }

	void setCamera(float _x, float _y) {
		this->cam_x = _x;
		this->cam_y = _y;
	}

	void GetCamera(float& x, float& y) { x = cam_x; y = cam_y; }


	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st, 
		float sr, 
		float sb,
		float &t, 
		float &nx, 
		float &ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	static CGame * GetInstance();

	bool CGame::isCollision(RECT r1, RECT r2)
	{
		return !(r1.right < r2.left || r1.left > r2.right || r1.top > r2.bottom || r1.bottom < r2.top);
	}

	HWND GetWindowHandle() { return hWnd; }

	~CGame();
};


