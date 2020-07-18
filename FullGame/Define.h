﻿#pragma once
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
#define SCREEN_WIDTH				560
#define SCREEN_HEIGHT				500	//460
#define SCREEN_PADING_TOP			80	//40

#define MAX_FRAME_RATE 50

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define ID_TEX 1
#define TIME_ENEMY_DIE 150
#define TIME_BOSS_DIE 500
#define BOSS_POSITION 5340.0f, 95.0f


#define BRICK_ANI					6
#define TORCH_ANI_FIRE				7
#define VAMPIREKILLER_1				8
#define VAMPIREKILLER_2				9
#define VAMPIREKILLER_3				10


#define SCENCE_0_LEFT 0
#define SCENCE_1_LEFT 0
#define SCENCE_2_LEFT 3084
#define SCENCE_3_LEFT 3074
#define SCENCE_4_LEFT 4096
#define SCENCE_5_LEFT 5122

#define SCENCE_0_RIGHT 1536
#define SCENCE_1_RIGHT 3084
#define SCENCE_2_RIGHT 4107
#define SCENCE_3_RIGHT 4107
#define SCENCE_4_RIGHT 5642
#define SCENCE_5_RIGHT 5642


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
	BRICK_1 = 21,
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
	OBJECT_HIDDEN_BLACKKNIGHT = 36,
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
	SMALLHEART = 54,
	CHICKEN = 55,
	MONEY_1 = 56,
	MONEY_2 = 57,
	MONEY_3 = 58,
	MONEY_4 = 59,
	MONEY_5 = 160,
	CLOCK = 60,
	ITEMAXE = 61,
	CROSS = 62,
	BOSSBALL = 63,
	ITEMII = 64,
	ITEMCLOCK = 65,
	ITEMCROSS = 66,
	ITEMHOLLYWATTER = 67,
	ITEMIII = 68,
	ITEMBOONGMERANG = 69,
	ITEMVASE = 70,

	// Enemy
	GHOST = 141,
	MINIGHOST = 142,
	BAT = 143, 
	BLACKKNIGHT = 144,
	WHITESKELETON = 145,
	FLEAMAN = 147,
	RAVEN = 148,

	//BOSS
	BOSS = 150,


	// id load
	ID_BRICK = 200,
	ID_TORCH = 201,
	ID_CANDLE = 205,
	ID_HIDDEN = 202,
	ID_GATE = 203,
	ID_ENEMY = 204
	
};

class Item;

#endif