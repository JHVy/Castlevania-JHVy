#include "Game.h"
#include "Axe.h"
#include "Torch.h"
//#include "Boss.h"
#include "HolyWater.h"
#include "Sound.h"

HollyWatter* HollyWatter::__instance = NULL;
HollyWatter::HollyWatter() :Weapon()
{
	AddAnimation(604);
	AddAnimation(820);
	isRender = false;
	state = HOLLY_WATTER_STATE_HIDE;
	start_attack = 0;
}
HollyWatter* HollyWatter::GetInstance()
{
	if (__instance == NULL) __instance = new HollyWatter();
	return __instance;
}

void HollyWatter::SetPosition(float simon_x, float simon_y)
{
	if (nx < 0)
	{
		x = simon_x + 5;
	}
	else {
		x = simon_x - 20;
	}

	y = simon_y;
}
void HollyWatter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (start_attack > 0)
	{
		if (GetTickCount() - start_attack > HOLLY_WATTER_TIME_ATTACK)
		{
			state = HOLLY_WATTER_STATE_HIDE;
			start_attack = 0;
			vy = -HOLLY_WATTER_SPEED_Y;
			isRender = false;
			animations[0]->ResetFrame();
		}
	}
	if (state == HOLLY_WATTER_STATE_ATTACK || state == HOLLY_WATTER_STATE_FIRE) {
		if (start_attack == 0)
		{
			start_attack = GetTickCount();
			isRender = true;
		}
		if (state == HOLLY_WATTER_STATE_ATTACK)
		{
			x += dt * vx;
			vy += GRAVITY * dt;
			y += vy * dt;
		}
		CollisionWithObject(dt, *coObjects);
	}
}

void HollyWatter::Render()
{
	if (state == HOLLY_WATTER_STATE_ATTACK) 
	{
		animations[0]->Render(x, y, nx, 255);
		//RenderBoundingBox();
	}
	else if(state == HOLLY_WATTER_STATE_FIRE)
	{
		
		if(animations[1]->GetCurrentFrame() == 0)
			animations[1]->Render(x, y, nx, 255);
		else
			animations[1]->Render(x - 10, y, nx, 255);
		//RenderBoundingBox();

	}

}

void HollyWatter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == HOLLY_WATTER_STATE_ATTACK)
	{
		left = x;
		right = x + 15;
		top = y;
		bottom = y + 15;
	}
	else if (state == HOLLY_WATTER_STATE_FIRE)
	{
		left = x;
		right = x + 30;
		top = y;
		bottom = y + 25;
	}

}
void HollyWatter::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (state != HOLLY_WATTER_STATE_HIDE)
	{
		RECT rect, rect1;
		float l, t, r, b;
		float l1, t1, r1, b1;

		GetBoundingBox(l, t, r, b);
		rect.left = (int)l;
		rect.top = (int)t;
		rect.right = (int)r;
		rect.bottom = (int)b;

		for (int i = 0; i < listObj.size(); i++)
		{
			if (dynamic_cast<Enemy*>(listObj.at(i)))
			{
				Enemy* enemy = dynamic_cast<Enemy*>(listObj.at(i));
				//if (enemy->GetState() == TORCH_STATE_EXSIST ||
					//((enemy->GetState() == BOSS_STATE_ATTACK || enemy->GetState() == BOSS_STATE_FLY) && enemy->GetType() == eType::BOSS))
				if (enemy->GetState() == TORCH_STATE_EXSIST)
				{

					enemy->GetBoundingBox(l1, t1, r1, b1);
					rect1.left = (int)l1;
					rect1.top = (int)t1;
					rect1.right = (int)r1;
					rect1.bottom = (int)b1;
					if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
					{
						Sound::GetInstance()->Play(eSound::soundHolyWater);
						if (enemy->GetType() == eType::BRICK_2)
						{
							vx = vy = 0;
							state = HOLLY_WATTER_STATE_FIRE;
							y -= 1;
							continue;
						}

						enemy->Hurt();

						if (enemy->GetEnergy() <= 0)
						{
							Simon* simon = Simon::GetInstance();
							if (enemy->GetType() == eType::GHOST)
								simon->SetScore(100);
							else if (enemy->GetType() == eType::PANTHER)
								simon->SetScore(300);
							else if (enemy->GetType() == eType::BAT)
								simon->SetScore(200);
							else if (enemy->GetType() == eType::FISHMEN)
								simon->SetScore(300);

							if (enemy->GetEnergy() <= 0)
							{
								if (enemy->GetType() == eType::BOSS)
								{
									//enemy->SetState(BOSS_STATE_NOT_EXSIST);
									simon->SetScore(1000);
								}
								else
								{
									enemy->SetState(TORCH_STATE_NOT_EXSIST);
								}
							}
						}

						state = HOLLY_WATTER_STATE_HIDE;
						isRender = false;
						break;
					}
				}
			}
		}
	}
}


void HollyWatter::SetState(int _state) {
	CGameObject::SetState(_state);
	if (state == HOLLY_WATTER_STATE_ATTACK)
	{
		vx = nx * HOLLY_WATTER_SPEED;
		vy = -HOLLY_WATTER_SPEED_Y;
	}
}