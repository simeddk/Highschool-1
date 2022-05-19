#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background_Mario.h"
#include "Objects/Marco.h"

Shader* shader = nullptr;
Marco* marco = nullptr;
Sprite* background = nullptr;

void InitScene()
{
	shader = new Shader(L"04_Sprite.fx");
	Context::Get()->SetShader(shader);

	marco = new Marco(shader, Vector2(100, 171), Vector2(2.5f, 2.5f));
	background = new Sprite(shader, L"Background/FinalFightStage.png");
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(background);
	SafeDelete(marco);
}

void Update()
{
	background->Update();
	marco->Update();
}

void Render()
{
	background->Render();
	marco->Render();
}