#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background_Mario.h"

Shader* shader = nullptr;
Sprite* marioSheet = nullptr;
Background_Mario* background = nullptr;

void InitScene()
{
	shader = new Shader(L"04_Sprite.fx");
	Context::Get()->SetShader(shader);

	background = new Background_Mario(shader);

	marioSheet = new Sprite(shader, L"MarioSheet.png", 70, 248, 117, 327);
	marioSheet->Position(700, 165);
	marioSheet->Scale(marioSheet->TextureSize());
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(marioSheet);
	SafeDelete(background);
}

void Update()
{
	background->Update();
	marioSheet->Update();
}

void Render()
{
	background->Render();
	marioSheet->Render();
}