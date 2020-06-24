#include "Candle.h"

void Candle::Render() {
	if (state == CANDLE_STATE_EXSIST) {
		CAnimations::GetInstance()->Get(this->numAnimation)->Render(x + SCREEN_PADING_TOP, y + SCREEN_PADING_TOP, 1, 255);
	}
	else if (state == CANDLE_STATE_ITEM) {
		if (item != NULL)
			item->Render();
	}
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
		right = x + CANDLE_WIDTH;
		bottom = y + CANDLE_HEIGHT;
	}
	else if (state == CANDLE_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
}