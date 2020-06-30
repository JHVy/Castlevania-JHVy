#include "Sprites.h"
#include "Game.h"
#include "Utils.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}
CSprite::CSprite()
{
	this->id = 0;
	this->left = 0;
	this->top = 0;
	this->right = 0;
	this->bottom = 0;
	this->texture = NULL;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha)
{
	//CGame* game = CGame::GetInstance();

	//DebugOut(L"[Draw] %f %f\n", x, y);

	CGame::GetInstance()->Draw(x, y, texture, left, top, right, bottom, alpha);
}

void CSprite::DrawFlipX(float x, float y, int alpha) {
	//DebugOut(L"[Draw FlipX] %f %f\n", x, y);

	LPD3DXSPRITE spriteHandler = CGame::GetInstance()->GetSpriteHandler();

	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;

	D3DXVECTOR2 top_left = D3DXVECTOR2(x, y);

	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &top_left, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;

	spriteHandler->SetTransform(&finalMt);

	x -= (right - left);

	this->DrawCam(x, y, alpha);

	spriteHandler->SetTransform(&oldMt);
}

void CSprite::DrawCam(float x, float y, int alpha)
{
	//CGame* game = CGame::GetInstance();
	CGame::GetInstance()->DrawFlipX(x, y, texture, left, top, right, bottom, alpha);
}

void CSprite::load(std::ifstream& inFile)
{
	string garbage;
	int idTexture;
	inFile >> garbage >> id;
	inFile >> garbage >> left;
	inFile >> garbage >> top;
	inFile >> garbage >> right;
	inFile >> garbage >> bottom;
	inFile >> garbage >> idTexture;
	CTextures* textures = CTextures::GetInstance();
	texture = textures->Get(idTexture);
}

// sprites
void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;

	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d \n", id, left, top, right, bottom);
}

void CSprites::Add(LPSPRITE lpsprite)
{
	sprites[lpsprite->getID()] = lpsprite;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

/*
	Clear all loaded textures
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}



