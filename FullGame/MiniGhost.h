#pragma once
#include "Enemy.h"

#define MINIGHOST_BBOX_WIDTH 32
#define MINIGHOST_BBOX_HEIGHT 32

//#define MINIGHOST_GRAVITY 0.05f

#define MINIGHOST_SPEED 0.085f
#define VY_GHOST	0.022f;
#define DEAD		1;
#define MINIGHOST_DISTANCE_TOO_FAR	300;


class Enemy;

class MiniGhost :public Enemy
{
	bool isStart;
	float _leftLimit;
	float _rightLimit;
public:
	MiniGhost(float _x, float _y, int id = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Start() { isStart = true; }
	void Stop() { isStart = false; }
	bool IsStart(); //{ return isStart; }
	bool Idle() { return !isStart; };
	void ChasingSimon(int x, int y);
};
