#pragma once

#include "ItemHeart.h"
#include "GameObject.h"
#include "Item.h"
#include "ItemUpgrade.h"
#include "ItemDagger.h"

#define TORCH_WIDTH 32
#define TORCH_HEIGHT 64
#define CANDLE_WIDTH 16
#define CANDLE_HEIGHT 32

#define TORCH_STATE_NOT_EXSIST 0
#define TORCH_STATE_EXSIST 1
#define TORCH_STATE_ITEM 2
#define TORCH_STATE_ITEM_NOT_EXSIST 3

#define ID_WHIPUPGRADE  1
#define ID_DAGGER		2
#define ID_HEART		3
#define ID_SMALLHEART	4
#define ID_CHICKEN		5
#define ID_MONEY_1		6
#define ID_MONEY_2		7
#define ID_MONEY_3		8
#define ID_MONEY_4		9
#define ID_BOSSBALL		10
#define ID_AXE   		11
#define ID_II			12
#define ID_CLOCK		13
#define ID_CROSS		14
#define ID_HOLLYWATTER	15
#define ID_BOONGMERANG	16
#define ID_VASE			17
#define ID_III			18

class Item_Heart;
class Item;

class Torch : public CGameObject
{
private:
	int numAnimation = 0;
	Item* item;

public:
	Torch(int _x, int _y) {
		this->_type = eType::TORCH;
		x = _x;
		y = _y;
		this->numAnimation = 501;
		this->state = TORCH_STATE_EXSIST;
	}

	Torch(int _x, int _y, int _id_item) {
		this->_type = eType::TORCH;
		x = _x;
		y = _y;
		this->numAnimation = 501;
		this->state = TORCH_STATE_EXSIST;

		switch (_id_item) {
		case ID_HEART:
			item = new Item_Heart(x, y);
			return;

		case ID_WHIPUPGRADE:
			item = new ItemUpgrade(x, y);
			return;

		case ID_DAGGER:
			item = new ItemDagger(x, y);
			return;

		default:
			return;
		}
	}

public:
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

