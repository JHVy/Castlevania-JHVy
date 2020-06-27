#include "Torch.h"

void Torch::Render() {
	if (state == TORCH_STATE_EXSIST) {
		CAnimations::GetInstance()->Get(this->numAnimation)->Render(x, y + SCREEN_PADING_TOP, w, -1, 255);
	}
	else if (state == TORCH_STATE_ITEM) {
		if (item != NULL)
			item->Render();
	}
}

void Torch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);

	if (state == TORCH_STATE_ITEM) {
		if (item != NULL)
			item->Update(dt, coObjects);
	}
}

void Torch::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + TORCH_WIDTH;
		bottom = y + TORCH_HEIGHT;
	}
	else if (state == TORCH_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
}