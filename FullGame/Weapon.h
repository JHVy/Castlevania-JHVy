#pragma once
#include "GameObject.h"

class Weapon: public CGameObject
{
protected:
	bool isRender;

public:
	Weapon() {}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	virtual CAnimation* GetAnimation() { if (animations.size() > 0)return animation; }
	virtual void Reset() {}
};

