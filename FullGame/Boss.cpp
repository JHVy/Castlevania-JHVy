#include "Boss.h"

#include "CastlevaniaScreen.h"

Boss* Boss::CurrentBoss = NULL;

Boss::Boss(float _x, float _y, int id) :Enemy(_x, _y, id)
{
	this->_type = eType::BOSS;
	animations.clear();
	AddAnimation(1090);
	AddAnimation(800);
	nx = 1;
	ny = 1;
	vx = SPEED_BOSS;
	vy = SPEED_BOSS;
	Simon::GetInstance()->GetPosition(bottomLimit, topLimit);
	bottomLimit = topLimit + 2 * SIMON_HEIGHT_STAND;
	topLimit -= SIMON_HEIGHT_STAND;
	isStart = false;
	_energy = 16;

	CurrentBoss = this;
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!this->IsStart())
		return;
	float c_x, c_y;
	CGame::GetInstance()->GetCamera(c_x, c_y);

	if (dt_die == 0)
	{
		if (state == TORCH_STATE_NOT_EXSIST)
		{
			dt_die = GetTickCount();
			if (item)
				item->SetPosition(x, y);
		}
		else
		{
			CGameObject::Update(dt);

			float xSimon, ySimon;
			Simon::GetInstance()->GetPosition(xSimon, ySimon);

			if (x > xSimon)
				nx = -1;
			else nx = 1;

			if (y > ySimon)
				ny = -1;
			if (y <= ySimon)
				ny = 1;

			if (rand() % RAND_MIN == 1 && (x > c_x - SCREEN_BOX_LEFT) && (x < c_x + SCREEN_BOX_RIGHT) && !target)
			{
				if (!fly)
				{
					vx = (float)(nx * abs(xSimon - x)) / MAX_DISTANCE;
					vy = (float)(ny * abs(ySimon - y)) / MAX_DISTANCE;
				}
				//checkstop = false;
			}

			if (abs(xSimon - x) <= 1.0f)
			{
				time = GetTickCount();
				vy = -VY_DOWN;
				if (rand() % 2 == 1)
					vx = VX_CLOSE;
				else
					vx = -VX_CLOSE;
				fly = true;
				checkstop = true;
			}

			if (GetTickCount() - time > TIME_ATTACK_STOP && checkstop)
			{
				vx = vy = 0;
				fly = false;
				target = false;
				checkstop = false;
			}


			if (x <= c_x - SCREEN_BOX_LEFT)
			{
				target = true;
				vx = VX_CLOSE;
				vy = -VY_DOWN;
				if (abs(x - xSimon) > MAX_DISTANCE_RIGHT_LEFT)
				{
					target = false;
				}
			}
			else if (x > c_x + SCREEN_BOX_RIGHT)
			{

				target = true;
				vx = -VX_CLOSE;
				if (rand() % 2 == 1)
					vy = VY;
				else
					vy = -VY;
				if (abs(x - xSimon) > MAX_DISTANCE_RIGHT_LEFT)
				{
					target = false;
				}
			}
			else if (y < c_y + SCREEN_BOX_UP)
			{
				target = true;
				vy = VY;
				if (abs(y - ySimon) > MAX_DISTANCE_UP_DOWN)
				{

					target = false;
				}
			}
			else if (y > c_y + SCREEN_BOX_DOWN)
			{
				target = true;
				vy = -VY_DOWN;
				if (abs(y - ySimon) > MAX_DISTANCE_UP_DOWN)
				{

					target = false;
				}
			}

			x += dx;
			y += dy;
		}
	}
	else
	{
		if (item != NULL) {//co item
			if (GetTickCount() - dt_die > TIME_ENEMY_DIE) // cho 150 mili second
			{
				item->Update(dt, coObjects);
				item->GetPosition(x, y);
				state = TORCH_STATE_ITEM;
			}
		}
	}

}

bool Boss::IsStart()
{
	float xSimon, ySimon;
	Simon::GetInstance()->GetPosition(xSimon, ySimon);

	if ((xSimon - x) > 150)
		isStart = true;

	if (isStart)
	{
		animations.clear();
		AddAnimation(1091);
	}
	return isStart;
}

void Boss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	//if (!Boss::IsStart())
		//return;
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + BOSS_BBOX_WIDTH;
		bottom = y + BOSS_BBOX_HEIGHT;
	}
	else if (state == TORCH_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
}
void Boss::Render()
{
	//if (!Boss::IsStart())
	//	return;

	if (state == TORCH_STATE_EXSIST)
	{
		animations[0]->Render(x, y, nx, 255);
	}
	else if (state == TORCH_STATE_ITEM)
	{
		if (item != NULL)
			item->Render();

	}
	else
	{
		if (GetTickCount() - dt_die < TIME_ENEMY_DIE)
		{
			animations[1]->Render(x, y);
		}
	}

	//RenderBoundingBox();
}