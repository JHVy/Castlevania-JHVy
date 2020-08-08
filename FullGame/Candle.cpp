#include "Candle.h"

void Candle::Render() {
	if (state == CANDLE_STATE_EXSIST) {
		CAnimations::GetInstance()->Get(this->numAnimation)->Render(x, y, 1, 255);
	}
	else if (state == CANDLE_STATE_ITEM) {
		if (item != NULL)
			item->Render();
	}
	//RenderBoundingBox();
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);

	if (state == CANDLE_STATE_ITEM) {
		if (item != NULL)
			item->Update(dt, coObjects);
	}
}

void Candle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == CANDLE_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}
	else if (state == CANDLE_STATE_ITEM)
	{
 		item->GetBoundingBox(left, top, right, bottom);
	}
}