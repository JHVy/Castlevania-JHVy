#pragma once
#include "GameObject.h"
//#include "Sound.h"

class VampireKiller;

class Weapon: public CGameObject
{
protected:
	bool isRender;
	bool is_using;

public:

	bool IsUsing() { return is_using; }
	void SetUsing(bool b) { is_using = b; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj);
	virtual CAnimation* GetAnimation() { if (animations.size() > 0) return animation; }
	virtual void Reset() {}
	virtual void Render() = 0;
};

