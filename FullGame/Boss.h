#pragma once
#include "Enemy.h"

#define BOSS_BBOX_WIDTH 32
#define BOSS_BBOX_HEIGHT 32

#define BOSS_LEFT_LIMIT 3080
#define BOSS_TOP_LIMIT 40
#define BOSS_RIGHT_LIMIT 4028
#define BOSS_BOTTOM_LIMIT 500

#define BOSS_DISTANCE_MOVING 200
#define BOSS_SPEED_X 0.1f
#define BOSS_SPEED_Y 0.04f
#define SPEED_BOSS	0.18f	

#define RAND_MIN 80
#define MAX_DISTANCE 900

#define SCREEN_BOX_LEFT -32
#define SCREEN_BOX_RIGHT 420
#define SCREEN_BOX_UP 100
#define SCREEN_BOX_DOWN 380

#define VY_DOWN 0.09
#define VX_CLOSE 0.12
#define VX 0.12
#define VY 0.05

#define TIME_ATTACK_STOP 1500
#define MAX_DISTANCE_RIGHT_LEFT 150
#define MAX_DISTANCE_UP_DOWN 100

class Boss : public Enemy
{
	float topLimit;
	float bottomLimit;
	bool isStart;
	bool checkactive,
		target,
		checkstop,
		fly;
	DWORD time, timeDelay;
public:
	static Boss* CurrentBoss;
	Boss(float _x = 3500, float _y = 200, int id = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Start() { isStart = true; }
	void Stop() { isStart = false; }
	bool IsStart();// { return isStart; }
};

