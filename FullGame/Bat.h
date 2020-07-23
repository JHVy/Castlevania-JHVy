#pragma once
#include "Enemy.h"

#define BAT_BBOX_WIDTH 32
#define BAT_BBOX_HEIGHT 32

#define BAT_LEFT_LIMIT 3080
#define BAT_TOP_LIMIT 40
#define BAT_RIGHT_LIMIT 4028
#define BAT_BOTTOM_LIMIT 500

#define BAT_DISTANCE_MOVING 200
#define BAT_SPEED_X 0.07f
#define BAT_SPEED_Y 0.04f

class Bat : public Enemy
{
	float topLimit;
	float bottomLimit;
	bool isStart;
public:
	Bat(float _x = 3500, float _y = 200, int id = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Start() { isStart = true; }
	void Stop() { isStart = false; }
	bool IsStart();// { return isStart; }
};

