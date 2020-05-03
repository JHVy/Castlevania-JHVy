#include "Item.h"


void Item::Render()
{
	if (state == ITEM_STATE_EXSIST)
	{
		/*if (animations.size() > 0)
			animations[this->numAnimation]->Render(x, y);*/
		CAnimations::GetInstance()->Get(this->numAnimation)->Render(x, y, 1, 255);
	}
	//RenderBoundingBox();
}


void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!time_exsist)
	{
		time_exsist = GetTickCount();
	}
	else
	{
		if (GetTickCount() - time_exsist >= TIME_ITEM_EXSIST)
			state = ITEM_STATE_NOT_EXSIST;
	}
	CGameObject::Update(dt);

	// Simple fall down
	y += ITEM_GRAVITY * dt;
	if (y >= 340) y = 340;
}
