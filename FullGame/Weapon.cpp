#include "Weapon.h"

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

	}
}
