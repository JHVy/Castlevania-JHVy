#include "GameConfig.h"
#include "Define.h"

GameConfig* GameConfig::_instance = NULL;

GameConfig* GameConfig::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new GameConfig();
	}
	return _instance;
}

GameConfig::GameConfig()
{
	CurrentLevel = 4;
	MaxLevel = 1;
	SimonPosition = NULL;
}

GameConfig::~GameConfig()
{
	SAFE_DELETE(SimonPosition);
}

void GameConfig::Load(string filePath)
{
	ifstream inFile;
	inFile.open(filePath);

	inFile >> MaxLevel;
	SimonPosition = new POINT[MaxLevel];

	for (int i = 0; i < MaxLevel; i++)
	{
		POINT p;
		int level;
		inFile >> level >> p.x >> p.y;

		SimonPosition[i] = p;
	}
}

void GameConfig::GetSimonPosition(float& x, float& y)
{
	x = (float)SimonPosition[CurrentLevel-1].x;
	y = (float)SimonPosition[CurrentLevel-1].y;
}