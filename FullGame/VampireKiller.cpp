#include "VampireKiller.h"
#include "Simon.h"
#include "Sound.h"

VampireKiller::VampireKiller() : Weapon()
{
	_level = 1;
	width = 120;
	height = 50;
	AddAnimation(600);
	AddAnimation(601);
	AddAnimation(602);
	animation = animations[0];
}

void VampireKiller::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (IsUsing())
		CollisionWithObject(dt, *coObjects);
}


void VampireKiller::SetPosition(float simon_x, float simon_y, int simon_state, int _nx)
{
	this->nx = _nx;
	y = simon_y;

	if (nx < 0)
	{
		if (simon_state == SIMON_STATE_SIT_ATTACK || simon_state == SIMON_STATE_SIT) 
		{
			x = simon_x;
			y = simon_y;
		}
		else
			x = simon_x;
	}
	else 
	{
		if (simon_state == SIMON_STATE_SIT_ATTACK || simon_state == SIMON_STATE_SIT) {
			x = simon_x;
			y = simon_y;
		}
		else
			x = simon_x;
	}
}


void VampireKiller::Render()
{
	int sprite_number = 600 + this->_level - 1;		//600 is VampireKiller
	LPANIMATION ani = CAnimations::GetInstance()->Get(sprite_number);

	ani->Render(x, y, nx, 255);

	//RenderBoundingBox();
}

void VampireKiller::Render(float simon_x, float simon_y, int simon_state, int _nx) {
	float x1, y1, nx1;
	nx1 = _nx;
	y1 = simon_y;
	x1 = simon_x;

	int sprite_number = 600 + this->_level - 1;
	LPANIMATION ani = CAnimations::GetInstance()->Get(sprite_number);
	ani->Render(x1, y1, nx, 255);
	RenderBoundingBox();
}

void VampireKiller::setDefaultLevel()
{
	_level = 1;
}

void VampireKiller::setUpLevel()
{
	Sound::GetInstance()->Play(eSound::soundCollectWeapon);
	if (_level < 3)
		_level++;
	animation = animations[_level - 1];
}

void VampireKiller::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	int sprite_number = 600 + this->_level - 1;
	LPANIMATION ani = CAnimations::GetInstance()->Get(sprite_number);
	//DebugOut(L"ani->GetCurrentFrame() %d\n", ani->GetCurrentFrame());
	if (ani->GetCurrentFrame() < 2)
		return;

	Weapon::GetBoundingBox(left, top, right, bottom);
}

void VampireKiller::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	Weapon::CollisionWithObject(dt, listObj);
}
