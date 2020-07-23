#include "BrickMoving.h"
#include "Utils.h"
#include "Simon.h"
#define BRICKMOVING_SPEED		0.05f


BrickMoving::BrickMoving(float _x, float _y, int id, int type, float width, float height)
	:Brick(_x, _y, id, type, width, height) 
{
	vx = BRICKMOVING_SPEED;
}

void BrickMoving::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Brick::Update(dt, coObjects);
	//DebugOut(L"[BrickMoving Update] %f\n", vx);
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT pObj = coObjects->at(i);
		if (dynamic_cast<Brick*>(pObj) && this->IsCollisedWith(pObj) && !dynamic_cast<BrickMoving*>(pObj))  //cham gach -> quay nguoc lai
		{
			vx = -vx;
			break;
		}
	}

	//DebugOut(L"[BrickMoving] %f\n", vx);
	dx = dt * vx;
	x += dx;

	// Update Simon
	Simon* simon = Simon::GetInstance();
	float simon_y = simon->y;
	simon->y += this->height;	//tam thoi tang y cua Simon len -> dich chuyen Simon thap xuong mot chut de check va cham
	if (simon->IsCollisedWith(this))
		simon->x += dx;
	simon->y = simon_y;	// tra ve vi tri y ban dau cua Simon
}

void BrickMoving::Render()
{
	RenderBoundingBox();
}

