#pragma once
#pragma once
#include "Enemy.h"

#define FLEAMAN_BBOX_WIDTH 32
#define FLEAMAN_BBOX_HEIGHT 32

#define FLEAMAN_SPEED 0.05f
#define FLEAMAN_GRAVITY 0.05f

#define FLEAMAN_DISTANCE_TOO_FAR 300
class Enemy;

class Fleaman :public Enemy
{
	static bool isStart;
	float _leftLimit;
	float _rightLimit;
public:
	Fleaman(float _x, float _y, int id = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	static void Start() { isStart = true; }
	static void Stop() { isStart = false; }
	bool IsStart(); //{ return isStart; }
	void CollisionWithBrick(DWORD dt, LPGAMEOBJECT& listBrick, float min_tx0, float min_ty0, int nx0, int ny0);
	void CollisionWithHiden(DWORD dt, LPGAMEOBJECT& listBrick, float min_tx0, float min_ty0, int nx0, int ny0);

};

