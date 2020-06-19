#include <iostream>
#include <fstream>

#include "Game.h"
#include "GameConfig.h"
#include "Utils.h"

#include "GameMap.h"
#include "Animations.h"

CGame* CGame::__instance = NULL;

/*
	Initialize DirectX, create a Direct3D device for rendering within the window, initial Sprite library for
	rendering 2D images
	- hInst: Application instance handle
	- hWnd: Application window handle
*/
void CGame::Init(HWND hWnd)
{
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	this->hWnd = hWnd;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	RECT r;
	GetClientRect(hWnd, &r);	// retrieve Window width & height 

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	screen_height = r.bottom + 1;
	screen_width = r.right + 1;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv);

	if (d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
		return;
	}

	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// Initialize sprite helper from Direct3DX helper library
	D3DXCreateSprite(d3ddv, &spriteHandler);

	OutputDebugString(L"[INFO] InitGame done;\n");

	// init params
	CastlevaniaScreen* scr = this->screens[this->current_scene];
	this->keyHandler = new CastkeKeyEventHandler(scr);
}

/*
	Utility function to wrap LPD3DXSPRITE::Draw
*/
void CGame::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha)
{
	float x1 = x - cam_x, y1 = y - cam_y;

	if (x1 + 70 >= 0 && x1 <= SCREEN_WIDTH && y1 + 70 >= 0 && y1 <= SCREEN_HEIGHT) 
	{
		D3DXVECTOR3 p(x1, y1, 0);
		//D3DXVECTOR3 p(150, 150, 0);
		RECT r;
		r.left = left;
		r.top = top;
		r.right = right;
		r.bottom = bottom;

		//DebugOut(L"[DRAW] sprite: position (%f, %f) - x1(%d, %d) - x2(%d , %d) - cam(%f, %f) \n", x, y, left, top, right, bottom, cam_x, cam_y);
		spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	}
}

void CGame::DrawFlipX(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha)
{
	float x1 = x + cam_x, y1 = y - cam_y;

	D3DXVECTOR3 p(x1, y1, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	//DebugOut(L"[DRAW] sprite: position (%f, %f) - x1(%d, %d) - x2(%d , %d) - cam(%f, %f) \n", x, y, left, top, right, bottom, cam_x, cam_y);
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));

}

void CGame::InitKeyboard()
{
	// init keyboard
	this->keyHandler->InitKeyBoard(hWnd);
}

void CGame::ProcessKeyboard()
{
	this->keyHandler->ProcessKeyBoard();
}

CGame::~CGame()
{
	if (spriteHandler != NULL) spriteHandler->Release();
	if (backBuffer != NULL) backBuffer->Release();
	if (d3ddv != NULL) d3ddv->Release();
	if (d3d != NULL) d3d->Release();
}

/*
	Standard sweptAABB implementation
	Source: GameDev.net
*/
void CGame::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float& t, float& nx, float& ny)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -999999.0f;
		tx_exit = 999999.0f;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999.0f;
		ty_exit = 99999.0f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}

CGame* CGame::GetInstance()
{
	if (__instance == NULL) __instance = new CGame();
	return __instance;
}

#define MAX_GAME_LINE 1024


#define GAME_FILE_SECTION_UNKNOWN -1
#define GAME_FILE_SECTION_SETTINGS 1
#define GAME_FILE_SECTION_SCENES 2

/*
	Load game campaign file and load/initiate first scene
*/
void CGame::Load()
{
	GameConfig::GetInstance()->Load("Res/config.txt");

	for (int i = 0; i <= GameConfig::GetInstance()->MaxLevel; i++)
	{
		CastlevaniaScreen* screen = new CastlevaniaScreen();
		this->screens[i] = screen;
	}
	
	this->current_scene = 1;

	SwitchScene(current_scene);
}

void CGame::SwitchScene(int scene_id)
{
	DebugOut(L"[INFO] Switching to scene %d\n", scene_id);

	this->screens[current_scene]->Unload();

	//CTextures::GetInstance()->Clear();
	//CSprites::GetInstance()->Clear();
	//CAnimations::GetInstance()->Clear();

	current_scene = scene_id;
	CastlevaniaScreen* s = this->screens[scene_id];

	s->Load();

	// init keyboard
	this->keyHandler->setCastleScreen(s);
}

// new version
void CGame::display() {
	// render screen
	this->screens[this->current_scene]->Render();
}

void CGame::Update(DWORD dt)
{
	if (current_scene != GameConfig::GetInstance()->CurrentLevel)
		SwitchScene(GameConfig::GetInstance()->CurrentLevel);

	GetCurrentScene()->Update(dt);
}