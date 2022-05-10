#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Rect.h"
#include "Objects/MovableRect.h"

Shader* shader = nullptr;
Sprite* scopeDog = nullptr;
Sprite* marioSheet = nullptr;
Sprite* marioSheet2 = nullptr;

void InitScene()
{
	shader = new Shader(L"04_Sprite.fx");
	Context::Get()->SetShader(shader);

	scopeDog = new Sprite(shader, L"Scopedog.png");
	scopeDog->Position(300, 300);
	scopeDog->Scale(200, 200);

	marioSheet = new Sprite(shader, L"MarioSheet.png", 70, 248, 117, 327);
	marioSheet->Position(650, 300);
	marioSheet->Scale(marioSheet->TextureSize());

	marioSheet2 = new Sprite(shader, L"MarioSheet.png", 194, 253, 246, 323);
	marioSheet2->Position(500, 600);
	marioSheet2->Scale(marioSheet->TextureSize());
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(scopeDog);
	SafeDelete(marioSheet);
	SafeDelete(marioSheet2);
}

void Update()
{
	scopeDog->Update();
	marioSheet->Update();
	marioSheet2->Update();
}

void Render()
{
	scopeDog->Render();
	marioSheet->Render();
	marioSheet2->Render();
}