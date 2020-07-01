#include "ItemHollyWatter.h"


void ItemHollyWatter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEM_HOLLYWATTER_WIDTH;
		top = y;
		bottom = y + ITEM_HOLLYWATTER_HEIGHT;
	}
}