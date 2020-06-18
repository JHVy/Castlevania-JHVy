#pragma once
#ifndef _DEFINE_H__
#define _DEFINE_H__

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "fstream"
#include <dinput.h>

using namespace std;

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Castlevania 1986 - JHVy"

#define BACKGROUND_COLOR_DEFAULT D3DCOLOR_XRGB(0, 0, 0)
#define BACKGROUND_COLOR_CROSS D3DCOLOR_XRGB(188, 188, 188)
#define SCREEN_WIDTH		520
#define SCREEN_HEIGHT		460

#define MAX_FRAME_RATE 50

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define ID_TEX 1


#define BRICK_ANI					6
#define TORCH_ANI_FIRE				7
#define VAMPIREKILLER_1				8
#define VAMPIREKILLER_2				9
#define VAMPIREKILLER_3				10


#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \

#endif

extern D3DCOLOR BACKGROUND_COLOR;


// ID của Sprite, object
enum eType
{
	SIMON = 1,
	SIMON_TRANS = 2,

	///
	// object nền
	GATE = 20,
	//BRICK_1 = 21,
	BRICK_2 = 22,
	//BRICK_3 = 23,
	//BRICK_4 = 24,
	//BRICK_5 = 25,


	// object
	OBJECT_HIDDEN_MONEY = 26,
	OBJECT_HIDDEN_GATE_OPEN = 27,
	OBJECT_HIDDEN_GHOST_UP = 28,
	OBJECT_HIDDEN_GHOST_DOWN = 29,
	OBJECT_HIDDEN_GHOST_2 = 30,
	TORCH = 31,
	OBJECT_HIDDEN_DOOR = 32,
	STAIR_UP = 33,
	STAIR_DOWN = 34,
	CANDLE = 35,
	OBJECT_HIDDEN_FISHMAN = 36,
	OBJECT_HIDDEN_GHOST_1 = 37,
	OBJECT_HIDDEN_GHOST_STOP_1 = 38,
	OBJECT_HIDDEN_PANTHER_JUMP = 39,
	OBJECT_HIDDEN_BRICK = 40,


	// weapon
	VAMPIREKILLER = 41,
	DAGGER = 42,
	AXE = 43,
	HOLLYWATTER = 44,
	BOONGMERANG = 45,

	// item
	HEART = 51,
	WHIPUPGRADE = 52,
	ITEMDAGGER = 53,
	


	// id load
	ID_BRICK = 200,
	ID_TORCH = 201,
	ID_HIDDEN = 202,
	
};

class Item;

#endif