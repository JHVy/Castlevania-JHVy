#pragma once
#pragma once
#include "Enemy.h"

#define FLEAMAN_BBOX_WIDTH 32
#define FLEAMAN_BBOX_HEIGHT 32

#define FLEAMAN_SPEED 0.2f
#define FLEAMAN_GRAVITY 0.05f
#define FLEAMAN_SPPED_Y_HIGH	-0.63f
#define FLEAMAN_SPEED_Y_LOW		-0.2f

#define FLEAMAN_DISTANCE_TOO_FAR 300

#define JUMP_HIGH				0
#define JUMP_LOW				1

#define AREA_TURNING			150
#define JUMP_RATE				2000
#define JUMP_RATE_MAX			10000

class Enemy;

class Fleaman :public Enemy
{
	bool isStart;
	float _leftLimit;
	float _rightLimit;
	int enemyState;
	bool firstJump;
	bool isGrounded;
public:
	Fleaman(float _x, float _y, int id = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Start() { isStart = true; }
	void Stop() { isStart = false; }
	bool IsStart(); //{ return isStart; }
	void CollisionWithBrick(DWORD dt, LPGAMEOBJECT& listBrick, float min_tx0, float min_ty0, int nx0, int ny0);
	void CollisionWithHiden(DWORD dt, LPGAMEOBJECT& listBrick, float min_tx0, float min_ty0, int nx0, int ny0);
	void ChasingSimon(int x, int y);
};

