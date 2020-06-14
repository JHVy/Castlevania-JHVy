#include "CBoard.h"

CBoard* CBoard::__instance = NULL;

CBoard* CBoard::GetInstance()
{
	if (__instance == NULL) __instance = new CBoard();
	return __instance;
}

void CBoard::Update(DWORD dt)
{
	
}
void CBoard::Render()
{

	CGame* game = CGame::GetInstance();
	float cx, cy;
	game->GetCamera(cx, cy);

	// Draw board 
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(50000)->Draw(cx + 540, cy);

	// Draw number
	code->DrawNumber(6, cx + 110, cy + 12, 500); // score
	code->DrawNumber(4, cx + 295, cy + 12, 300); // time
	code->DrawNumber(2, cx + 465, cy + 12, 1); // state
	code->DrawNumber(2, cx + 400, cy + 32, 1); // heart
	code->DrawNumber(2, cx + 400, cy + 52, 1);

	// Draw energy bar
	code->DrawEnergyBar(cx + 110, cy + 30, 0, 5); // player
	code->DrawEnergyBar(cx + 110, cy + 50, 1, 5); // enemy

}