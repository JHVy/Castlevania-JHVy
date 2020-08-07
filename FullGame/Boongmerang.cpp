#include "Game.h"
#include "Torch.h"
//#include "Boss.h"
#include "Boongmerang.h"
#include "Sound.h"

Boongmerang* Boongmerang::__instance = NULL;
Boongmerang::Boongmerang() :Weapon()
{
	AddAnimation(605);
	isRender = false;
	state = BOONGMERANG_STATE_HIDE;
	start_attack = 0;
	turn = 0;
}
Boongmerang* Boongmerang::GetInstance()
{
	if (__instance == NULL) __instance = new Boongmerang();
	return __instance;
}

void Boongmerang::SetPosition(float simon_x, float simon_y)
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
void Boongmerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!IsUsing())
		return;

	if (start_attack > 0)
	{
		if (GetTickCount() - start_attack > BOONGMERANG_TIME_ATTACK)
		{
			state = BOONGMERANG_STATE_HIDE;
			start_attack = 0;
			isRender = false;
			float c_y;
			CGame::GetInstance()->GetCamera(leftLimit, c_y);
			rightLimit = leftLimit + SCREEN_WIDTH;
			vx = nx * BOONGMERANG_SPEED;
			turn = 0;
		}
	}
	if (state == BOONGMERANG_STATE_ATTACK) {
		if (start_attack == 0)
		{
			start_attack = GetTickCount();
			isRender = true;
		}

		x += dt * vx;
		if ((x < leftLimit && vx < 0) || (x > rightLimit&& vx > 0))
		{
			vx = -vx;
			nx = -nx;
			turn++;
		}
		if(turn < 2)
			CollisionWithObject(dt, *coObjects);


	}
}

void Boongmerang::Render()
{
	if (!IsUsing())
		return;

	if (state == BOONGMERANG_STATE_ATTACK && turn < 2) {
		animations[0]->Render(x, y, nx, 255);
		//RenderBoundingBox();
	}
}

void Boongmerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BOONGMERANG_STATE_ATTACK)
	{
		left = x;
		right = x + 40;
		top = y;
		bottom = y + 20;
	}

}

void Boongmerang::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	Weapon::CollisionWithObject(dt, listObj);

	//if (state == BOONGMERANG_STATE_ATTACK)
	//{
	//	RECT rect, rect1;
	//	float l, t, r, b;
	//	float l1, t1, r1, b1;

	//	GetBoundingBox(l, t, r, b);
	//	rect.left = (int)l;
	//	rect.top = (int)t;
	//	rect.right = (int)r;
	//	rect.bottom = (int)b;

	//	for (int i = 0; i < listObj.size(); i++)
	//	{
	//		if (dynamic_cast<Enemy*>(listObj.at(i)))
	//		{
	//			Enemy* enemy = dynamic_cast<Enemy*>(listObj.at(i));
	//			if (enemy->GetState() == TORCH_STATE_EXSIST)
	//			{

	//				enemy->GetBoundingBox(l1, t1, r1, b1);
	//				rect1.left = (int)l1;
	//				rect1.top = (int)t1;
	//				rect1.right = (int)r1;
	//				rect1.bottom = (int)b1;
	//				if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
	//				{
	//					Sound::GetInstance()->Play(eSound::soundHurting);

	//					if (enemy->GetType() == eType::BRICK_2)
	//					{
	//						continue;
	//					}
	//					enemy->Hurt();

	//					if (enemy->GetEnergy() <= 0)
	//					{
	//						Simon* simon = Simon::GetInstance();
	//						if (enemy->GetType() == eType::GHOST)
	//							simon->SetScore(100);

	//						if (enemy->GetEnergy() <= 0)
	//						{
	//							if (enemy->GetType() == eType::BOSS)
	//							{
	//								//enemy->SetState(BOSS_STATE_NOT_EXSIST);
	//								simon->SetScore(1000);
	//							}
	//							else
	//							{
	//								enemy->SetState(TORCH_STATE_NOT_EXSIST);
	//							}
	//						}
	//					}
	//					isRender = false;
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}
}


void Boongmerang::SetState(int _state) {
	CGameObject::SetState(_state);
	if (state == BOONGMERANG_STATE_ATTACK)
	{
		vx = nx * BOONGMERANG_SPEED;
		if (!start_attack)
			start_attack = GetTickCount();
		float c_y;
		CGame::GetInstance()->GetCamera(leftLimit, c_y);
		rightLimit = leftLimit + SCREEN_WIDTH;
	}
}