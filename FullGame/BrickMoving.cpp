#include "BrickMoving.h"
#include "Utils.h"
#include "Simon.h"
#define BRICKMOVING_SPEED		0.05f


BrickMoving::BrickMoving(float _x, float _y, int id, int type, float width, float height)
	:Brick(_x, _y, id, type, width, height) 
{
	animations.clear();
	AddAnimation(1300);
	vx = BRICKMOVING_SPEED;
}

void BrickMoving::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->DistanceTo(Simon::GetInstance()) >= 2*CAM_PADDING)
		return;

	vector<LPGAMEOBJECT> list;
	for (int i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT pObj = coObjects->at(i);
		if (dynamic_cast<Brick*>(pObj) && !dynamic_cast<BrickMoving*>(pObj))
		{
			list.push_back(coObjects->at(i));
		}
	}

	Brick::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(&list, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny_1;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny_1);
		
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame

		if (nx != 0)
		{
			this->vx *= -1;
		}
		
	}
	list.clear();
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];



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
	//RenderBoundingBox();
	animations[0]->Render(x, y, nx, 255);
}

