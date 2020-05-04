#include "ItemDagger.h"

void ItemDagger::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ITEM_STATE_EXSIST)
	{
		left = x;
		right = x + ITEMDAGGER_WIDTH;
		top = y;
		bottom = y + ITEMDAGGER_HEIGHT;
	}
}