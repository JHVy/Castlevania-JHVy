#include "ItemUpgrade.h"

void ItemUpgrade::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEMUPGRADE_WIDTH;
		top = y;
		bottom = y + ITEMUPGRADE_HEIGHT;
	}
}
