#pragma once
#include "GameObject.h"
#include "Game.h"
#include "CCode.h"
#include "Simon.h"


#define SCORE_X 110
#define SCORE_Y 12


class CBoard
{
	int _time;
	DWORD _count;
	CCode* code;
	static CBoard* __instance;

	int _weapon;
	int _numberOfWeapon;

public:
	static CBoard* GetInstance();
	CBoard()
	{
		_time = 300;
		_count = GetTickCount();
		code = new CCode();
		_weapon = 0;
		_numberOfWeapon = 0;
	}

	~CBoard()
	{
		if (code != NULL)
			delete code;
		code = NULL;
	}

	void Update(DWORD dt);
	void Render();
	void SetWeapon(int weapon) { _weapon = weapon; }
	int GetWeapon() { return _weapon; }
};
