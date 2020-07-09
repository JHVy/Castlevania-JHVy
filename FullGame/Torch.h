#pragma once

#include "ItemHeart.h"
#include "GameObject.h"
#include "Item.h"
#include "ItemUpgrade.h"
#include "ItemDagger.h"

#define TORCH_WIDTH 32
#define TORCH_HEIGHT 64


#define TORCH_STATE_NOT_EXSIST 0
#define TORCH_STATE_EXSIST 1
#define TORCH_STATE_ITEM 2
#define TORCH_STATE_ITEM_NOT_EXSIST 3

#define ID_WHIPUPGRADE  1
#define ID_DAGGER		2
#define ID_HEART		3
#define ID_SMAILLHEART	4
#define ID_BOONGMERANG	5


class Item_Heart;
class Item;

class Torch : public CGameObject
{
protected:
	int numAnimation = 0;
	Item* item;

public:
	Torch(int _x, int _y) {
		this->width = TORCH_WIDTH;
		this->_type = eType::TORCH;		//default is Torch
		x = _x;
		y = _y;
		this->numAnimation = 501;
		this->state = TORCH_STATE_EXSIST;
	}

	Torch(int _x, int _y, int _id_item) {
		this->_type = eType::TORCH;		//default is Torch
		x = _x;
		y = _y;
		this->width = TORCH_WIDTH;
		this->numAnimation = 501;
		this->state = TORCH_STATE_EXSIST;

		switch (_id_item) 
		{
		case ID_HEART:
			item = new ItemHeart(x, y);
			return;

		case ID_WHIPUPGRADE:
			item = new ItemUpgrade(x, y);
			return;

		case ID_DAGGER:
			item = new ItemDagger(x, y);
			return;


		default:
			item = NULL;
			return;
		}
	}

public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int getItemType() {
		return this->item->getItemType();
	}

	void invisibleItem() {
		this->item->StartInvisible();
	}
};

