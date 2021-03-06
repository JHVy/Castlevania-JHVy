﻿#include "Weapon.h"
#include "Torch.h"
#include "Candle.h"
#include "Enemy.h"
#include "BrickBreak.h"

void Weapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> listObj;
	// Collision logic with items
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT object = coObjects->at(i);
		listObj.push_back(object);
	}

	CollisionWithObject(dt, listObj);
}


void Weapon::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	for (int i = 0; i < listObj.size(); i++)
	{
		if (dynamic_cast<BrickBreak*>(listObj.at(i)))
		{
			BrickBreak* brickBreak = (BrickBreak*)listObj.at(i);
			if (brickBreak->GetState() == TORCH_STATE_EXSIST)
			{
				if (this->IsCollisedWith(brickBreak)) //đụng độ
				{
					brickBreak->Hurt();
					SetUsing(false);
					isRender = false;
				}
			}
		}
		else if (dynamic_cast<Enemy*>(listObj.at(i)))
		{
			Enemy* enemy = (Enemy*)listObj.at(i);
			if (enemy->GetState() == TORCH_STATE_EXSIST)
			{
				if (this->IsCollisedWith(enemy)) //đụng độ
				{
					enemy->Hurt();
					SetUsing(false);
					isRender = false;
				}
			}
		}
		else if (dynamic_cast<Torch*>(listObj.at(i)))
		{
			if (listObj.at(i)->GetState() == TORCH_STATE_EXSIST)
			{
				if (this->IsCollisedWith(listObj.at(i))) //đụng độ
				{
					listObj.at(i)->SetState(TORCH_STATE_ITEM);
					SetUsing(false);
					isRender = false;
				}
			}
		}
		else if (dynamic_cast<Candle*>(listObj.at(i)))
		{
			if (listObj.at(i)->GetState() == CANDLE_STATE_EXSIST)
			{
				if (this->IsCollisedWith(listObj.at(i))) //đụng độ
				{
					listObj.at(i)->SetState(CANDLE_STATE_ITEM);
					SetUsing(false);
					isRender = false;
				}
			}
		}
	}
}
