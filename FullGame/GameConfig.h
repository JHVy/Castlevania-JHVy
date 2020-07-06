#pragma once
#include <Windows.h>

#include <signal.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <vector>


using namespace std;
class Simon;
class GameConfig
{
private:
	static GameConfig* _instance;
	POINT* SimonPosition;

public:
	int CurrentLevel, MaxLevel;

	GameConfig();
	~GameConfig();
	static GameConfig* GetInstance();

	void Load(string filePath);
	void LevelUp() { SetGameLevel(++CurrentLevel); }
	void SetGameLevel(int level) 
	{ 
		if (level <= MaxLevel) 
			CurrentLevel = level;
		else
			CurrentLevel = MaxLevel;
	}

	void GetSimonPosition(float& x, float& y);
};

