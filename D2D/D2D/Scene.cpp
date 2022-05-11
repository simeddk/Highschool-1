#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background_Mario.h"

Shader* shader = nullptr;
Background_Mario* background = nullptr;
Clip* clip = nullptr;

void InitScene()
{
	shader = new Shader(L"04_Sprite.fx");
	Context::Get()->SetShader(shader);

	background = new Background_Mario(shader);

	clip = new Clip(EPlayType::Loop);
	clip->AddFrame(new Sprite(shader, L"Tarma.png", 4, 2, 34, 40), 0.22f);
	clip->AddFrame(new Sprite(shader, L"Tarma.png", 35, 2, 64, 40), 0.22f);
	clip->AddFrame(new Sprite(shader, L"Tarma.png", 64, 2, 94, 40), 0.22f);
	clip->Play();
	//clip->Speed(5.2f);

	clip->Position(100, 170);
	clip->Scale(2.5f, 2.5f);
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(background);
	SafeDelete(clip);
}

void Update()
{
	background->Update();
	clip->Update();
}

void Render()
{
	background->Render();
	clip->Render();
}