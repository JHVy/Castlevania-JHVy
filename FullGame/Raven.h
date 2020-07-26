#pragma once
#include "Enemy.h"

#define RAVEN_BBOX_WIDTH 30
#define RAVEN_BBOX_HEIGHT 32

#define RAVEN_LEFT_LIMIT 3080
#define RAVEN_TOP_LIMIT 40
#define RAVEN_RIGHT_LIMIT 4028
#define RAVEN_BOTTOM_LIMIT 500

class Raven : public Enemy
{
	float topLimit;
	float bottomLimit;
	bool delayTime;
	bool isStart;
public:
	Raven(float _x = 3500, float _y = 200, int id = 0);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void Start() { isStart = true; }
	void Stop() { isStart = false; }
	bool IsStart();// { return isStart; }
};

