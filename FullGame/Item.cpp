#include "Item.h"


void Item::Render()
{
	if (state == ITEM_STATE_EXSIST)
	{
		/*if (animations.size() > 0)
			animations[this->numAnimation]->Render(x, y);*/
		CAnimations::GetInstance()->Get(this->numAnimation)->Render(x + SCREEN_PADING_TOP, y + SCREEN_PADING_TOP, 1, 255);
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
		/*if (GetTickCount() - time_exsist >= TIME_ITEM_EXSIST)
			state = ITEM_STATE_NOT_EXSIST;*/

		if (time_start_invisible != 0 && GetTickCount() - time_start_invisible >= TIME_TO_INVISIBLE)
			state = ITEM_STATE_NOT_EXSIST;
	}
	CGameObject::Update(dt);

	y += ITEM_GRAVITY * dt; 
	if (y >= 310) y = 310;   // HARD code item roi
}
