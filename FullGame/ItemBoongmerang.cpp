#include "ItemBoongmerang.h"

void ItemBoongmerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEMBOONGMERANG_WIDTH;
		top = y;
		bottom = y + ITEMBOONGMERANG_HEIGHT;
	}
}
