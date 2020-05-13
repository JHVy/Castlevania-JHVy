#include "Simon.h"
#include "Game.h"

Simon::Simon() {
	VampireKiller* rob = new VampireKiller();
	vampireKiller = rob;
	vampireKiller->setUpLevel();
	vampireKiller->setUpLevel();

	untouchable = 0;
	trans_start = 0;
	start_jump = 0;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	// collision
	if (!coObjects->empty() && IsAttacking()) {
		RECT rect, rect1, rectSimon;

		// weapon vs item
		float l = 0, t = 0, r = 0, b = 0;
		if (vampireKiller)
			this->vampireKiller->GetBoundingBox(l, t, r, b);


		rect.left = (int)l;
		rect.top = (int)t;
		rect.right = (int)r;
		rect.bottom = (int)b;
		
		// simon vs item
		float ls = 0, ts = 0, rs = 0, bs = 0;
		ls = 0;
		rs = 0;
		ts = 0;
		bs = 0;

		if (vampireKiller)
			this->vampireKiller->GetBoundingBox(ls, ts, rs, bs);

		rectSimon.left = (int)ls;
		rectSimon.top = (int)ts;
		rectSimon.right = (int)rs;
		rectSimon.bottom = (int)bs;

		for (int index = 0; index < coObjects->size(); index++) {
			LPGAMEOBJECT obj = coObjects->at(index);

			if (obj->_type != eType::TORCH)
				continue;
			
			float l1, t1, r1, b1;
			obj->GetBoundingBox(l1, t1, r1, b1);
			
			rect1.left = (int)l1;
			rect1.top = (int)t1;
			rect1.right = (int)r1;
			rect1.bottom = (int)b1;

			if (CGame::GetInstance()->isCollision(rect, rect1)) {
				obj->SetState(TORCH_STATE_ITEM);
			}

			if (CGame::GetInstance()->isCollision(rectSimon, rect1)) {
				if (obj->GetState == TORCH_STATE_ITEM)
					this->vampireKiller->setUpLevel();
			}
		}

		
	}

	// update
	x = x + 0.75 * vx * dt;
	y = y + vy * dt;
	vy += 0.2 * SIMON_GRAVITY * dt;

	if (x < 30) x = 30;

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

	 if (state == SIMON_STATE_DIE)
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
			vampireKiller->Render(x, y, state, nx);
			vampireKiller->SetPosition(x, y, state, nx);
		}
	}
	else if (state == SIMON_STATE_STAND_ATTACK)
	{
		id = SIMON_ANI_STANDING_ATTACKING;

		if (start_jump)
			id = SIMON_ANI_SITTING_ATTACKING;

		if (vampireKiller != NULL) {
			vampireKiller->Render(x, y, state, nx);
			vampireKiller->SetPosition(x, y, state, nx);
		}

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


	DebugOut(L"[START DRAW SIMON] ");
	LPANIMATION ani = CAnimations::GetInstance()->Get(id);

	int x1 = x, y1 = y;
	if (id == SIMON_ANI_SITTING || id == SIMON_ANI_SITTING_ATTACKING)
		y1 = y1 + 15;
	ani->Render(x1, y1, nx, alpha);

}

void Simon::SetState(int state)
{
	// need update
	DebugOut(L"[SIMON-SETSTATE] %d\n", state);

	int currentTime = GetTickCount();

	if (attack_start)
		return;

	if (start_jump && state != SIMON_STATE_STAND_ATTACK) 
		return;


	
	switch (state) {
	case SIMON_STATE_STAND_ATTACK:
		if (attack_start || currentTime - last_attack < ATTACK_TIME_WAIT)
			return;

		attack_start = GetTickCount();
		last_attack = attack_start + ATTACK_TIME;

		this->vampireKiller->GetAnimation()->ResetFrame();
		break;

	case SIMON_STATE_SIT_ATTACK:
		if (attack_start || currentTime - last_attack < ATTACK_TIME_WAIT)
			return;

		attack_start = GetTickCount();
		last_attack = attack_start + ATTACK_TIME;
		this->vampireKiller->GetAnimation()->ResetFrame();
		break;

	case SIMON_STATE_JUMP:
		if (start_jump || currentTime - last_jump < JUMP_WAIT_TIME)
			break;

		start_jump = GetTickCount();
		last_jump = start_jump;
		vy = -SIMON_JUMP_SPEED_Y;
		y = 300;
		break;

	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		vy = 0;
		y = 300;
		break;

	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		vy = 0;
		y = 300;
		break;

	case SIMON_STATE_SIT:
		vx = 0;
		vy = 0;
		break;

	default:
		break;
	}

	this->state = state;

	return;
}


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
	else if ( state == SIMON_STATE_SIT_ATTACK
		|| (state == SIMON_STATE_SIT)
		|| (start_jump > 0 && GetTickCount() - start_jump <= SIMON_TIME_STATE_JUMP))
	{
		bottom = this->y + SIMON_HEIGHT_SIT;
	}

}