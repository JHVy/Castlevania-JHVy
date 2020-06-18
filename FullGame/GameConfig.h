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
	void LevelUp() { if (CurrentLevel < MaxLevel) ++CurrentLevel; }
	void GetSimonPosition(float& x, float& y);
};

