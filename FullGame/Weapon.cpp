#include "Weapon.h"
#include "Torch.h"

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
		if (dynamic_cast<Torch*>(listObj.at(i)))
		{
			if (listObj.at(i)->GetState() == TORCH_STATE_EXSIST)
			{
				LPCOLLISIONEVENT e = SweptAABBEx(listObj.at(i));
				if (e->t > 0) //đụng độ
				{
					listObj.at(i)->SetState(TORCH_STATE_ITEM);
				}
			}
		}
	}
}
