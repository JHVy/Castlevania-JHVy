#include "BrickBreak.h"
#include "Sound.h"

void BrickBreak::Hurt()
{
	Sound::GetInstance()->Play(eSound::soundBrokenBrick);
	this->SetState(CANDLE_STATE_ITEM);

	// Disappear Brick with ID
	vector<LPGAMEOBJECT>* listObj = Simon::GetInstance()->GetListObject();
	for (int i = 0; i < listObj->size(); i++)
	{
		if (dynamic_cast<Brick*>(listObj->at(i)))
		{
			Brick* brick = (Brick*)listObj->at(i);

			if (brick->GetID() == this->IdBrick)
				brick->Disappear();
		}
	}
}


void BrickBreak::RenderBlackBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_BLACK_BBOX);

	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = height;

	CGame::GetInstance()->Draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 255);
}

void BrickBreak::Render()
{
	if (state != CANDLE_STATE_EXSIST) 
		RenderBlackBox();

	if (state == CANDLE_STATE_EXSIST) 
	{
		//RenderBoundingBox();
	}
	else if (state == CANDLE_STATE_ITEM) 
	{
		if (item != NULL)
			item->Render();
	}
}

