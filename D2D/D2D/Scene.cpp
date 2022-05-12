#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background_Mario.h"
#include "Objects/Marco.h"

Shader* shader = nullptr;
Background_Mario* background = nullptr;
Marco* marco = nullptr;

void InitScene()
{
	shader = new Shader(L"04_Sprite.fx");
	Context::Get()->SetShader(shader);

	background = new Background_Mario(shader);
	marco = new Marco(shader, Vector2(100, 171), Vector2(2.5f, 2.5f));
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