#include "Simon.h"

Simon::Simon() {
	VampireKiller* rob = new VampireKiller();
	vampireKiller = rob;

	untouchable = 0;
	trans_start = 0;
	_heart = 5;
	isCanOnStair = 0;
	isOnStair = false;
	_stairTrend = 0;
	_energy = SIMON_MAX_ENERGY;
	isAutoGo = false;
	auto_x = -1;
	_score = 0;
	_lives = 99;
	_count = 0;
	start_stair = 0;
	isFall = false;
	isUnder = false;
	start_disappear = 0;
	start_jump = 0;

	//AddAnimation(400);		//0. idle left 
	//AddAnimation(401);		//1. walk left
	//AddAnimation(402);		//2. jump left
	//AddAnimation(403);		//3. sit left
	//AddAnimation(404);		//4. stand attack
	//AddAnimation(405);		//5. sit attack
	//AddAnimation(399);		//6. trans
	//AddAnimation(406);		//7. go up
	//AddAnimation(407);		//8. go down
	//AddAnimation(408);		//9. hurt
	//AddAnimation(409);		//10. idle up
	//AddAnimation(410);		//11. idle down
	//AddAnimation(411);		//12. die
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	x = x + 0.75 * vx * dt;
	y = y + vy * dt;
	vy += 0.2 * SIMON_GRAVITY * dt;

	if (y > 300) {
		y = 300;
		vy = 0;
		vx = 0;
		start_jump = 0;
	}

	if (attack_start) {
		int t = GetTickCount();

		if (t - attack_start > ATTACK_TIME) {
			attack_start = 0;
			this->state = SIMON_STATE_IDLE;
			return;
		}

		return;
	}
}

void Simon::Render()
{
	int id;

	if (isAutoGo)
	{
		id = SIMON_ANI_WALKING;
	}
	else if (state == SIMON_STATE_DIE)
	{
		id = SIMON_ANI_DIE;
	}
	else if (state == SIMON_STATE_IDLE_DOWN)
	{
		id = SIMON_ANI_IDLE_DOWN;
	}
	else if (state == SIMON_STATE_IDLE_UP)
	{
		id = SIMON_ANI_IDLE_UP;
	}
	else if (state == SIMON_STATE_SIT_ATTACK)
	{
		id = SIMON_ANI_SITTING_ATTACKING;

		if (vampireKiller != NULL) {
			vampireKiller->SetPosition(x, y, state, nx);
			vampireKiller->Render();
		}
	}
	else if (state == SIMON_STATE_STAND_ATTACK)
	{
		id = SIMON_ANI_STANDING_ATTACKING;

		if (vampireKiller != NULL) {
			vampireKiller->SetPosition(x, y, state, nx);
			vampireKiller->Render();
		}

	}
	else if (state == SIMON_STATE_GO_UP && (isCanOnStair == 1 || isOnStair))
	{
		id = SIMON_ANI_GO_UP;
	}
	else if (state == SIMON_STATE_GO_DOWN)
	{
		if (isOnStair)
			id = SIMON_ANI_GO_DOWN;
		else
			id = SIMON_ANI_SITTING;
	}
	else if (state == SIMON_STATE_ATTACK_DAGGER)
	{
		id = SIMON_ANI_STANDING_ATTACKING;
	}
	else if (state == SIMON_STATE_SIT)
	{
		id = SIMON_ANI_SITTING;

	}
	else if (state == SIMON_STATE_JUMP)
	{
		if (start_jump > 0)
			id = SIMON_ANI_JUMPING;
		else
			id = SIMON_ANI_IDLE;
	}
	else if (state == SIMON_STATE_HURT)
	{
		id = SIMON_ANI_HURT;
	}
	else {
		if (vx == 0)
		{
			id = SIMON_ANI_IDLE;
		}
		else
		{
			id = SIMON_ANI_WALKING;
		}
	}
	if (trans_start > 0) {
		id = SIMON_ANI_TRANS;
	}
	int alpha = 255;
	if (untouchable
		&& (isOnStair || GetTickCount() - untouchable_start > SIMON_HURT_TIME)
		&& (die_start == 0)) alpha = 128;
	if (start_disappear)
	{
		alpha = (GetTickCount() - start_disappear) / 1000 * 50;
	}

	DebugOut(L"[START DRAW SIMON] ");
	//id = SIMON_ANI_STANDING_ATTACKING;
	LPANIMATION ani = CAnimations::GetInstance()->Get(id);
	ani->Render(x, y, nx, alpha);

}

void Simon::SetState(int state)
{
	// need update
	DebugOut(L"[SIMON-SETSTATE] %d\n", state);

	if (attack_start)
		return;

	if (start_jump && state != SIMON_STATE_STAND_ATTACK) 
		return;


	this->state = state;
	switch (state) {
	case SIMON_STATE_STAND_ATTACK:
		if (attack_start)
			return;

		attack_start = GetTickCount();
		this->vampireKiller->GetAnimation()->ResetFrame();
		break;

	case SIMON_STATE_JUMP:
		if (start_jump)
			break;

		start_jump = GetTickCount();
		vy = -SIMON_JUMP_SPEED_Y;
		break;

	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		vy = 0;
		break;

	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		vy = 0;
		break;

	case SIMON_STATE_SIT:
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}

	return;
}


//if (attack_start > 0)
//{

//}
//else if (trans_start > 0) {

//}
//else if (die_start > 0) {

//}
//else if (isAutoGo)
//{

//}
//else if (untouchable && GetTickCount() - untouchable_start < SIMON_HURT_TIME)
//{

//}
//else if (getAnimation(SIMON_ANI_GO_UP)->GetCurrentFrame() > 0 && isOnStair)
//{

//}
//else if (getAnimation(SIMON_ANI_GO_DOWN)->GetCurrentFrame() > 0 && isOnStair)
//{

//}
//else if (state == SIMON_STATE_JUMP)
//{
//	if (!start_jump)
//	{
//		if (y < _ground + 1 && y > _ground - 1 && !untouchable) {
//			vy = -SIMON_JUMP_SPEED_Y;
//			start_jump = GetTickCount();
//			if (this->state == SIMON_STATE_IDLE)
//				vx = 0;
//		}
//	}
//}
//else
//{
//	//CGameObject::SetState(state);
//	switch (state)
//	{
//	case SIMON_STATE_WALKING_RIGHT:
//		vx = SIMON_WALKING_SPEED;
//		nx = 1;
//		break;
//	case SIMON_STATE_WALKING_LEFT:
//		vx = -SIMON_WALKING_SPEED;
//		nx = -1;
//		break;
//	case SIMON_STATE_SIT_ATTACK:
//		attack_start = GetTickCount();
//		//Sound::GetInstance()->Play(eSound::soundWhip);
//		getAnimation(SIMON_ANI_SITTING_ATTACKING)->ResetFrame();
//		vampireKiller->GetAnimation()->ResetFrame();
//		vx = 0;
//		break;
//	case SIMON_STATE_SIT:
//		y = 272.0f;
//		vx = 0;
//		break;
//	case SIMON_STATE_STAND_ATTACK:
//		attack_start = GetTickCount();
//		//Sound::GetInstance()->Play(eSound::soundWhip);
//		getAnimation(SIMON_ANI_STANDING_ATTACKING)->ResetFrame();
//		vampireKiller->GetAnimation()->ResetFrame();
//		vx = 0;
//		break;

//	case SIMON_STATE_UP:
//		y -= 15;

//	case SIMON_STATE_IDLE:
//		vx = 0;
//		break;
//	case SIMON_STATE_GO_UP:
//		if (isOnStair)
//		{
//			if (start_stair == 0)
//			{
//				start_stair = GetTickCount();
//				if (!isUnder)
//				{
//					new_y = y - PER_STEP;
//					if (_stairTrend == 0)
//						new_x = x + PER_STEP;
//					else
//						new_x = x - PER_STEP;
//				}
//				else
//				{
//					new_y = y;
//					new_x = x + 100;
//					isUnder = false;
//				}
//			}
//			break;
//		}
//		if (isCanOnStair != 1)
//		{
//			state = SIMON_STATE_IDLE;
//			vx = 0;
//		}
//		else
//		{
//			isOnStair = true;

//			if (abs(auto_x - x) > 0.5f)
//				isAutoGo = true;
//		}
//		break;
//	case SIMON_STATE_GO_DOWN:
//		if (isOnStair)
//		{
//			if (start_stair == 0)
//			{
//				start_stair = GetTickCount();
//				if (!isUnder)
//				{
//					new_y = y + PER_STEP;
//					if (_stairTrend == 0)
//						new_x = x - PER_STEP;
//					else
//						new_x = x + PER_STEP;
//				}
//				else
//				{
//					new_y = y;
//					new_x = x - 100;
//					isUnder = false;
//				}
//			}
//			break;
//		}

//		if (isCanOnStair != -1)
//		{
//			this->state = SIMON_STATE_SIT;
//			vx = 0;
//		}
//		else
//		{
//			isOnStair = true;

//			if (abs(auto_x - x) > 0.5f)
//				isAutoGo = true;
//		}
//		break;
//	case SIMON_STATE_IDLE_UP:
//	case SIMON_STATE_IDLE_DOWN:
//		vx = vy = 0;
//		break;

//	}
//}
//}

void Simon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = this->x;
	top = this->y;
	right = this->x + SIMON_WIDTH;
	bottom = this->y + SIMON_HEIGHT_STAND;
	if (state == SIMON_STATE_DIE)
	{
		right = this->x + SIMON_WIDTH_DIE;
		bottom = this->y + SIMON_HEIGHT_DIE;
	}
	else if ((state == SIMON_STATE_GO_DOWN && isCanOnStair != -1)
		|| state == SIMON_STATE_SIT_ATTACK
		|| (state == SIMON_STATE_SIT)
		|| (start_jump > 0 && GetTickCount() - start_jump <= SIMON_TIME_STATE_JUMP))
	{
		bottom = this->y + SIMON_HEIGHT_SIT;
	}

}