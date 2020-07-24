#pragma once
#include"Candle.h"

#define ENEMY_WALKING_SPEED 0.05f;

#define ENEMY_STATE_WALKING 100
#define ENEMY_STATE_DIE 200

#define ENEMY_ANI_WALKING 0
#define ENEMY_ANI_DIE 1

#define TIME_APPEAR     1000

class Enemy : public Candle
{
	bool isStop;

protected:
	int ny;
	float start_x, start_y;
	DWORD dt_die;
	DWORD dt_appear;
	int _energy;
public:
	int GetEnergy() { return _energy; }
	virtual void Hurt() { _energy -= 2; }

	Enemy(float _x, float _y, int id = 0) : Candle(_x, _y, id)
	{
		start_x = _x;
		start_y = _y;
		_energy = 1;
	}
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) = 0;
	virtual void Reset() {}
	virtual void Dead() { state = CANDLE_STATE_NOT_EXSIST; }
	virtual bool Idle() { return false; }
};