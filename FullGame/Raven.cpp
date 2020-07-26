#include "Raven.h"

#include "CastlevaniaScreen.h"


Raven::Raven(float _x, float _y, int id) :Enemy(_x, _y, id)
{
	isStart = false;
	this->_type = eType::RAVEN;
	animations.clear();
	AddAnimation(1008);
	AddAnimation(800);
	vx = -0.07f;
	vy = 0.04f;
	nx = -1;
	ny = 1;
	Simon::GetInstance()->GetPosition(bottomLimit, topLimit);
	bottomLimit = topLimit + 2 * SIMON_HEIGHT_STAND;
	topLimit -= SIMON_HEIGHT_STAND;
}

bool Raven::IsStart()
{
	if (this->DistanceTo(Simon::GetInstance()) <= 200)
	{
		isStart = true;
	}

	if (isStart)
	{
		animations.clear();
		AddAnimation(1009);
	}
	return isStart;
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
			Simon::GetInstance()->GetPosition(bottomLimit, topLimit);
			bottomLimit = topLimit + 2 * SIMON_HEIGHT_STAND;
			topLimit -= SIMON_HEIGHT_STAND;
			if ((x <= c_x && nx < 0) || (x >= c_x + SCREEN_WIDTH && nx > 0))
			{
				vx = -vx;
				nx = -nx;
			}
			if ((y <= topLimit && ny < 0) || (y >= bottomLimit && ny > 0))
			{
				vy = -vy;
				ny = -ny;
			}
			CGameObject::Update(dt);
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
void Raven::Render()
{
	/*if (!Raven::IsStart())
		return;*/
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