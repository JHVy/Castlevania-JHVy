#pragma once
//#include "Game.h"
#include "GameObject.h"
#include "Define.h"
#include "Weapon.h"
#include "VampireKiller.h"
#include "Utils.h"

#define SIMON_WALKING_SPEED		0.12f
#define SIMON_JUMP_SPEED_Y		0.36f
#define SIMON_GRAVITY			0.001f

#define SIMON_POS_Y				300

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_SIT			    400
#define SIMON_STATE_STAND_ATTACK	500
#define SIMON_STATE_SIT_ATTACK		600
#define SIMON_STATE_DIE				700
#define SIMON_STATE_UP				800
#define SIMON_STATE_ATTACK_DAGGER	900
#define SIMON_STATE_GO_UP			1000
#define SIMON_STATE_GO_DOWN			1001
#define SIMON_STATE_IDLE_UP			1002
#define SIMON_STATE_IDLE_DOWN		1003
#define SIMON_STATE_HURT			1100

#define SIMON_ANI_IDLE						400
#define SIMON_ANI_WALKING					401
#define SIMON_ANI_JUMPING					402
#define SIMON_ANI_SITTING					403
#define SIMON_ANI_STANDING_ATTACKING 		404
#define SIMON_ANI_SITTING_ATTACKING			405
#define SIMON_ANI_TRANS						399
#define SIMON_ANI_GO_UP 					406
#define SIMON_ANI_GO_DOWN					407
#define SIMON_ANI_HURT						408
#define SIMON_ANI_IDLE_UP					409
#define SIMON_ANI_IDLE_DOWN					410
#define SIMON_ANI_DIE						411

#define SIMON_HEIGHT_STAND			60
#define SIMON_HEIGHT_SIT			45
#define SIMON_WIDTH					33
#define SIMON_HEIGHT_DIE			30
#define SIMON_WIDTH_DIE				60


#define ID_WEAPON_VAMPIREKILLER		0
#define ID_WEAPON_DAGGER			1

#define ATTACK_TIME			300
#define ATTACK_TIME_WAIT	300
#define JUMP_TIME			0
#define JUMP_WAIT_TIME 1000


#define SIMON_STRANS_TIME 400
#define SIMON_TIME_PER_STEP 200
#define SIMON_STRANS_TIME 400
#define SIMON_TIME_STATE_JUMP 400
#define SIMON_TIME_START_JUMP 1000


class CGame;
class Simon;
class VampireKiller;
class Weapon;

class Simon :
	public CGameObject
{
protected:
	int untouchable;
	DWORD untouchable_start;
	DWORD trans_start;
	DWORD attack_start;
	DWORD start_jump;

	//Sound* sound;

	int _energy;
	int _score;
	int _lives;
	int _heart;

	static Simon* _instance;

	unordered_map<int, Weapon*> weapons;
	bool isFall;

	
	// history
	int last_attack = 0;
	int last_jump = 0;

	// weapon 
	VampireKiller* vampireKiller;

public:

	static Simon* GetInstance();

	Simon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	// check state
	bool IsAttacking() { if (attack_start > 0) return true; return false; }
	bool IsSitting() {
		if (this->state == SIMON_STATE_SIT || this->state == SIMON_STATE_SIT_ATTACK)
			return true;
		return false;
	}

	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int GetEnergy()
	{
		return _energy;
	}

	int GetScore()
	{
		return _score;
	}

	int GetLives()
	{
		return _lives;
	}

	int GetHeart()
	{
		return _heart;
	}
private:
	// helper
	CAnimation* getAnimation(int id) {
		return CAnimations::GetInstance()->Get(id);
	}
};

