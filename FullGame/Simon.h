#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Weapon.h"
#include "VampireKiller.h"

#define SIMON_WALKING_SPEED		0.12f
#define SIMON_JUMP_SPEED_Y		0.36f
#define SIMON_GRAVITY			0.005f

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

#define SIMON_UNTOUCHABLE_TIME		1300
#define SIMON_HURT_TIME				500

#define ID_WEAPON_VAMPIREKILLER		0
#define ID_WEAPON_DAGGER			1

#define ATTACK_TIME			300
#define ATTACK_TIME_WAIT	700
#define JUMP_TIME			0
#define DIE_TIME			2000
#define TIME_FOR_PER_STEP  200

#define SIMON_STRANS_TIME 400
#define SIMON_TIME_PER_STEP 200
#define SIMON_STRANS_TIME 400
#define SIMON_TIME_STATE_JUMP 400
#define SIMON_TIME_START_JUMP 1000
#define SIMON_SPEED_ON_STAIR 1.23f
#define SIMON_DISAPPEAR_TIME 5000

#define SIMON_DISTANCE_FLASH 500.0f

#define TIME_RATE_END_GAME 50

#define ONE_HIT 2

class Simon :
	public CGameObject
{
protected:
	int untouchable;
	DWORD untouchable_start;
	DWORD trans_start;
	DWORD attack_start;
	DWORD _count;
	DWORD die_start;
	DWORD start_stair;
	DWORD start_jump;
	DWORD start_disappear;
	//Sound* sound;
	unordered_map<int, Weapon*> weapons;
	//vector<CWaterEffection*> list;
	bool isFall;

	int _heart;
	int isCanOnStair;
	bool isOnStair;
	int _stairTrend;
	bool isAutoGo;
	int auto_x;
	int _score;
	int _lives;
	int _step;
	float _ground;
	float new_x;
	float new_y;
	bool isUnder;
	float start_x, start_y;

	// weapon 
	VampireKiller* vampireKiller;

public:
	Simon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();

	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

