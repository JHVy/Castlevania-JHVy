#include "Bat.h"

#include "CastlevaniaScreen.h"

Bat::Bat(float _x, float _y, int id):Enemy(_x, _y, id)
{
	this->_type = eType::BAT;
	animations.clear();
	AddAnimation(1001);
	AddAnimation(800);
	nx = 1;
	ny = 1; 

	vx = SPEED_BAT;
	vy = SPEED_BAT;
	Simon::GetInstance()->GetPosition(bottomLimit, topLimit);
	bottomLimit = topLimit + 2 * SIMON_HEIGHT_STAND;
	topLimit -= SIMON_HEIGHT_STAND;
	isStart = false;
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!this->IsStart())
		return;
	float c_x, c_y;
	CGame::GetInstance()->GetCamera(c_x, c_y);
	
	if (dt_die == 0)
	{
		if (state == CANDLE_STATE_NOT_EXSIST) 
		{
			dt_die = GetTickCount();
			if (item)
				item->SetPosition(x, y);
		}
		else
		{
			CGameObject::Update(dt);

			x += dx;
			r += dy;
			if (r < RANGE)
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
				state = CANDLE_STATE_ITEM;
			}
		}
	}

}

bool Bat::IsStart()
{ 
	float xSimon, ySimon;
	Simon::GetInstance()->GetPosition(xSimon, ySimon);

	if (abs(x - xSimon) < 210 && abs(y - ySimon) < 80)
		isStart = true;

	if (isStart)
	{
		animations.clear();
		AddAnimation(1002);
	}
	return isStart; 
}

void Bat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	//if (!Bat::IsStart())
		//return;
	if (state == TORCH_STATE_EXSIST)
	{
		left = x;
		top = y;
		right = x + BAT_BBOX_WIDTH;
		bottom = y + BAT_BBOX_HEIGHT;
	}
	else if (state == TORCH_STATE_ITEM)
	{
		item->GetBoundingBox(left, top, right, bottom);
	}
}
void Bat::Render()
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
			if (animations.size() > 1)
				animations[1]->Render(x, y);
		}
	}
}