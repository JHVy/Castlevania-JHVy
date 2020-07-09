#include "Game.h"
#include "Dagger.h"
#include "Torch.h"
#include "Sound.h"
//#include "Sound.cpp"
//#include "Boss.h"

Dagger* Dagger::__instance = NULL;
Dagger::Dagger() :Weapon()
{
	animations.clear();
	vx = 0.5f;
	AddAnimation(701);
	state = DAGGER_STATE_HIDE;
	start_attack = 0;
	isRender = false;
}

Dagger* Dagger::GetInstance()
{
	if (__instance == NULL) __instance = new Dagger();
	return __instance;
}

void Dagger::SetPosition(float simon_x, float simon_y)
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
void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (start_attack > 0)
	{
		CollisionWithObject(dt, *coObjects);
		if (GetTickCount() - start_attack > DAGGER_TIME_ATTACK)
		{
			state = DAGGER_STATE_HIDE;
			start_attack = 0;
			isRender = false;

		}
	}
	if (state == DAGGER_STATE_ATTACK) {
		if (start_attack == 0)
		{
			start_attack = GetTickCount();
			isRender = true;
		}
		if (nx > 0)
			x += dt * vx;
		else
			x -= dt * vx;
		

	}
}

void Dagger::Render()
{
	if (isRender) {
		//animations[0]->Render(x, y, nx, 255);
		RenderBoundingBox();
	}
}

void Dagger::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == DAGGER_STATE_ATTACK && isRender)
	{
		left = x;
		right = x + 40;
		top = y;
		bottom = y + 20;
	}

}
void Dagger::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (state == DAGGER_STATE_ATTACK)
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
				//	((enemy->GetState() == BOSS_STATE_ATTACK || enemy->GetState() == BOSS_STATE_FLY) && enemy->GetType() == eType::BOSS))
				if(enemy->GetState() == TORCH_STATE_EXSIST)
				{
					if (enemy->GetType() == eType::BRICK_2)
						continue;
					enemy->GetBoundingBox(l1, t1, r1, b1);
					rect1.left = (int)l1;
					rect1.top = (int)t1;
					rect1.right = (int)r1;
					rect1.bottom = (int)b1;
					if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
					{
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
						isRender = false;
						Sound::GetInstance()->Play(eSound::soundHurting);
						break;
					}
				}
			}
		}
	}
}


