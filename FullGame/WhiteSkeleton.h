#pragma once
#include "Enemy.h"

#define WHITESKELETON_BBOX_WIDTH 40
#define WHITESKELETON_BBOX_HEIGHT 60

#define WHITESKELETON_SPEED 0.05f
#define WHITESKELETON_GRAVITY 0.05f
#define SKELETON_SPEED_X		0.12f
#define SKEKETON_SPEED_Y		0.4f

#define WHITESKELETON_DISTANCE_TOO_FAR 300
#define AREA_ACTIVE 240
#define AREA_TURNING1 180
#define AREA_TURNING2 30
#define AREA_TURNING3 210
#define AREA_TURNING4 60

#define JUMP 0
#define WALK 1
class Enemy;

class WhiteSkeleton :public Enemy
{
	bool isStart;
	float _leftLimit;
	float _rightLimit;
	int enemyState;
	int isGrounded;
public:
	WhiteSkeleton(float _x, float _y, int id = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Start() { isStart = true; }
	void Stop() { isStart = false; }
	bool IsStart(); // { return isStart; }
	//void CollisionWithBrick(DWORD dt, LPGAMEOBJECT& listBrick, float min_tx0, float min_ty0, int nx0, int ny0);
	//void CollisionWithHiden(DWORD dt, LPGAMEOBJECT& listBrick, float min_tx0, float min_ty0, int nx0, int ny0);
	void ChasingSimon(int x, int y);
};