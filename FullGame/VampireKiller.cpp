#include "VampireKiller.h"


VampireKiller::VampireKiller() :Weapon()
{
	_level = 1;
	AddAnimation(600);
	AddAnimation(601);
	AddAnimation(602);
	animation = animations[0];
}

void VampireKiller::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> listObj;
	// Collision logic with items

	CollisionWithObject(dt, *coObjects);
}

void VampireKiller::SetPosition(float simon_x, float simon_y, int simon_state)
{
	if (_level == 1 || _level == 2)
	{
		if (nx < 0)
		{
			if (simon_state == SIMON_STATE_SIT_ATTACK)
				x = simon_x - 40;
			else
				x = simon_x - 45;
		}
		else {
			if (simon_state == SIMON_STATE_SIT_ATTACK)
				x = simon_x - 15;
			else
				x = simon_x - 10;
		}
	}
	else
	{
		if (nx < 0)
		{
			x = simon_x - 75;
		}
		else {
			x = simon_x - 10;
		}
	}
	y = simon_y;

}

void VampireKiller::Render()
{
	animation->Render(x, y, nx, 255);
	y += 15;
	if (animation->GetCurrentFrame() < 2)
		return;
	RenderBoundingBox();
}

void VampireKiller::setDefaultLevel()
{
	_level = 1;
}

void VampireKiller::setUpLevel()
{
	if (_level < 3)
		_level++;
	animation = animations[_level - 1];
}

void VampireKiller::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (animation->GetCurrentFrame() < 2)
		return;
	if (_level == 1 || _level == 2)
	{
		left = x;
		right = x + 120;
		top = y;
		bottom = y + 20;
	}
	else
	{
		left = x;
		right = x + 145;
		top = y;
		bottom = y + 20;

	}
}


void VampireKiller::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (animation->GetCurrentFrame() < 2)
		return;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&listObj, coEvents);

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


