#include "Raven.h"

#include "CastlevaniaScreen.h"


Raven::Raven(float _x, float _y, int id) :Enemy(_x, _y, id)
{
	isStart = false;
	
	this->_type = eType::RAVEN;
	this->enemyState = RAVEN_IDLE;
	timeStop = 0;

	animations.clear();
	AddAnimation(1009);
	AddAnimation(800);
	
	vx = SPEED_RAVEN;
	vy = SPEED_RAVEN;
	nx = -1;
	ny = 1;
	Simon::GetInstance()->GetPosition(bottomLimit, topLimit);

	bottomLimit = topLimit + 2 * SIMON_HEIGHT_STAND;
	topLimit -= SIMON_HEIGHT_STAND;

	this->Start();
}

void Raven::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!this->IsStart())
		return;

	float c_x, c_y;
	CGame::GetInstance()->GetCamera(c_x, c_y);

	if (dt_die == 0)
	{
		if (state == TORCH_STATE_NOT_EXSIST) {
			dt_die = GetTickCount();
			if (item)
				item->SetPosition(x, y);
		}
		else
		{
			float xSimon, ySimon;
			Simon::GetInstance()->GetPosition(xSimon, ySimon);

			if (abs(x - xSimon) < RANGE_ACTIVE)
				enemyState = RAVEN_FLY;

			if (enemyState == RAVEN_IDLE)
				return;

			CGameObject::Update(dt);
			x += dx;
			y += dy;

			ChasingSimon(xSimon, ySimon);
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
void Raven::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	/*if (!Raven::IsStart())
		return;*/
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + RAVEN_BBOX_WIDTH;
		bottom = y + RAVEN_BBOX_HEIGHT;
	}
	else if (state == TORCH_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
}

void Raven::ChasingSimon(int xS, int yS)
{
	if (y < yS)
	{
		if (x > xS)
		{
			nx = -1;
			vx = -SPEED_RAVEN;
			if (abs(x - xS) < RANGE_STOP)
			{
				vx = 0;
				vy = 0;
				timeStop++;
				if (timeStop < TIME_STOP1)
					return;
				vx = -SPEED_RAVEN;
				vy = SPEED_RAVEN;
			}
			if (abs(x - xS) < RANGE_STOP / 2)
			{
				vx = 0;
				vy = 0;
				timeStop++;
				if (timeStop < TIME_STOP2)
					return;
				vx = -SPEED_RAVEN;
				vy = SPEED_RAVEN;
			}
		}
		else
		{
			nx = 1;
			vx = SPEED_RAVEN;
			if (abs(x - xS) < RANGE_STOP)
			{
				vx = 0;
				vy = 0;
				timeStop++;
				if (timeStop < TIME_STOP1)
					return;
				vx = SPEED_RAVEN;
				vy = SPEED_RAVEN;
			}
			if (abs(x - xS) < RANGE_STOP / 2)
			{
				vx = 0;
				vy = 0;
				timeStop++;
				if (timeStop < TIME_STOP2)
					return;
				vx = SPEED_RAVEN;
				vy = SPEED_RAVEN;
			}
		}
	}
	else
	{
		vx = 0;
		vy = -SPEED_RAVEN;
	}
}
void Raven::Render()
{
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