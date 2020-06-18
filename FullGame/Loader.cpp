#include "Loader.h"

void LoadSpriteResource() {
	DebugOut(L"[INFO] Start load resource \n");
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_BBOX, L"Res\\textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX, L"Res\\textures\\texture.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX, L"Res\\maps\\map2.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 tex = textures->Get(ID_TEX);

	TiXmlDocument doc("Sprites.xml");
	if (!doc.LoadFile())
	{
		printf("%s", doc.ErrorDesc());
		return;
	}
	TiXmlElement* root = doc.RootElement();

	TiXmlElement* sprite = nullptr;
	int id, left, top, right, bottom;

	for (sprite = root->FirstChildElement(); sprite != NULL; sprite = sprite->NextSiblingElement())
	{
		sprite->QueryIntAttribute("id", &id);
		sprite->QueryIntAttribute("left", &left);
		sprite->QueryIntAttribute("top", &top);
		sprite->QueryIntAttribute("right", &right);
		sprite->QueryIntAttribute("bottom", &bottom);
		CSprite* sprite = new CSprite(id, left, top, right, bottom, tex);
		sprites->Add(sprite);
	}

	int animationID, frameTime;
	LPANIMATION ani;

	TiXmlDocument doc1("Animations.xml");
	if (!doc1.LoadFile())
	{
		printf("%s", doc1.ErrorDesc());
		return;
	}
	TiXmlElement* root1 = doc1.RootElement();

	TiXmlElement* animation = nullptr;
	for (animation = root1->FirstChildElement(); animation != NULL; animation = animation->NextSiblingElement())
	{
		animation->QueryIntAttribute("animationID", &animationID);
		animation->QueryIntAttribute("frameTime", &frameTime);
		ani = new CAnimation(frameTime);
		TiXmlElement* sprite = animation->FirstChildElement();
		for (sprite = animation->FirstChildElement(); sprite != NULL; sprite = sprite->NextSiblingElement())
		{
			int id;
			sprite->QueryIntAttribute("id", &id);
			ani->Add(id);
		}
		animations->Add(animationID, ani);
	}

	#pragma region Add sprites Map
	//Map1
	/*textures->Add(ID_TEX_MAP1, L"Res\\maps\\map1.png", D3DCOLOR_XRGB(255, 0, 255));
	int index = 0;
	int rowMap = 6, colMap = 24, sizeTile = 64;
	for (int i = 0; i < rowMap; i++)
	{
		for (int j = 0; j < colMap; j++)
		{
			sprites->Add(index++, j * sizeTile, i * sizeTile, (j + 1) * sizeTile, (i+1) * sizeTile, textures->Get(ID_TEX_MAP1));
		}
	}*/

	//Map2
	/*textures->Add(ID_TEX_MAP2, L"Res\\maps\\map2.png", D3DCOLOR_XRGB(255, 0, 255));
	int index = 0;
	int rowMap = 12, colMap = 16, sizeTile = 64;
	for (int i = 0; i < rowMap; i++)
	{
		for (int j = 0; j < colMap; j++)
		{
			sprites->Add(index++, j * sizeTile, i * sizeTile, (j + 1) * sizeTile, (i + 1) * sizeTile, textures->Get(ID_TEX_MAP2));
		}
	}*/

}