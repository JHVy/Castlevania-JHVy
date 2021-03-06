#pragma once

#include "Weapon.h"
#include "Simon.h"

class VampireKiller: public Weapon
{
	int _level;

	static VampireKiller* _instance;

public:
	VampireKiller();

	static VampireKiller* GetInstance();

	void SetPosition(float simon_x, float simon_y);
	void Render();
	void Render(float simon_x, float simon_y, int simon_state, int nx);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void setDefaultLevel();
	void setUpLevel();
	void Reset() { _level = 1; animation = animations[0]; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);

	CAnimation* GetAnimation() { return CAnimations::GetInstance()->Get(600); }
};

