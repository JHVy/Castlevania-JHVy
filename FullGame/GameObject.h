#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Define.h"
#include "Sprites.h"
#include "Animations.h"


using namespace std;

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	
	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:
	int id;

	// toa do
	float x; 
	float y;

	// quang duong di chuyen
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	// van toc
	float vx;
	float vy;

	int nx;	 

	int state;

	// thoi gian di chuyen
	DWORD dt; 

	int _type;
	int _energy;

	unordered_map<int, LPANIMATION> animations;
	LPANIMATION animation;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	// Get/Set phuong huong de lat anh
	void SetTrend(int nx) { this->nx = nx; }
	int GetTrend() { return nx; }

	int GetType() { return _type; }

	int GetState() { return this->state; }

	void RenderBoundingBox();

	//void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	CGameObject(float _x = 0, float _y = 0, int type = 0);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	void AddAnimation(int aniId);

	int GetID() { return id; }
	void SetID(int id) { this->id = id; }

	int GetEnergy() { return _energy; }
	virtual void Hurt() { _energy -= 2; }
	virtual void Go() {}

	~CGameObject();
};

