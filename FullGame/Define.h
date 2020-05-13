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
#define MAIN_WINDOW_TITLE L"Castlevania 1986"

#define BACKGROUND_COLOR_DEFAULT D3DCOLOR_XRGB(0, 0, 0)
#define BACKGROUND_COLOR_CROSS D3DCOLOR_XRGB(188, 188, 188)
#define SCREEN_WIDTH 520
#define SCREEN_HEIGHT 460

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


	// object
	TORCH = 31,
	CANDLE = 35,
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