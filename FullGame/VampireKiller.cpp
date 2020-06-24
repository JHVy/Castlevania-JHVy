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
	//CollisionWithObject(dt, *coObjects);
}


void VampireKiller::SetPosition(float simon_x, float simon_y, int simon_state, int _nx)
{
	this->nx = _nx;
	y = simon_y;

	if (nx < 0)
	{
		if (simon_state == SIMON_STATE_SIT_ATTACK || simon_state == SIMON_STATE_SIT) {
			x = simon_x - 50;
			y = simon_y + 15;
		}
		else
			x = simon_x - 50;
	}
	else {
		if (simon_state == SIMON_STATE_SIT_ATTACK || simon_state == SIMON_STATE_SIT) {
			x = simon_x - 25;
			y = simon_y + 15;
		}
		else
			x = simon_x - 25;
	}
}


void VampireKiller::Render()
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(600);
	ani->Render(x, y, nx, 255);

	// RenderBoundingBox();
}

void VampireKiller::Render(float simon_x, float simon_y, int simon_state, int _nx) {
	float x1, y1, nx1;
	simon_y += SCREEN_PADING_TOP;
	nx1 = _nx;
	y1 = simon_y;
	x1 = x;

	if (_level < 3) {
		if (_nx < 0)
		{
			if (simon_state == SIMON_STATE_SIT_ATTACK || simon_state == SIMON_STATE_SIT) {
				x1 = simon_x + 25;
				y1 = simon_y + 15;
			}
			else
				x1 = simon_x + 25;
		}
		else {
			if (simon_state == SIMON_STATE_SIT_ATTACK || simon_state == SIMON_STATE_SIT) {
				x1 = simon_x + 35;
				y1 = simon_y + 15;
			}
			else
				x1 = simon_x + 35;
		}
	}
	else {
		if (_nx < 0)
		{
			if (simon_state == SIMON_STATE_SIT_ATTACK || simon_state == SIMON_STATE_SIT) {
				x1 = simon_x + 45;
				y1 = simon_y + 15;
			}
			else
				x1 = simon_x + 45;
		}
		else {
			if (simon_state == SIMON_STATE_SIT_ATTACK || simon_state == SIMON_STATE_SIT) {
				x1 = simon_x - 55;
				y1 = simon_y + 15;
			}
			else
				x1 = simon_x + 55;
		}
	}

	if (nx < 0)
		x1 = x1 + 20;
	else
		x1 += 80;

	int sprite_number = 600 + this->_level - 1;
	LPANIMATION ani = CAnimations::GetInstance()->Get(sprite_number);
	ani->Render(x1, y1, nx, 255);
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
	int sprite_number = 600 + this->_level - 1;
	LPANIMATION ani = CAnimations::GetInstance()->Get(sprite_number);
	if (ani->GetCurrentFrame() < 2)
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

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		RECT rect, rect1;
		float l, t, r, b;
		float l1, t1, r1, b1;

		GetBoundingBox(l, t, r, b);
		rect.left = (int)l;
		rect.top = (int)t;
		rect.right = (int)r;
		rect.bottom = (int)b;

		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
	}
}
