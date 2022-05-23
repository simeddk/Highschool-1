#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background_Mario.h"
#include "Objects/Marco.h"

Shader* shader = nullptr;
Marco* marco = nullptr;
Marco* marco2 = nullptr;
Sprite* background = nullptr;
PerFrame* perFrame = nullptr;

void InitScene()
{
	shader = new Shader(L"04_Sprite.fx");

	marco = new Marco(shader, Vector2(100, 140), Vector2(2.5f, 2.5f));
	Context::Get()->SetFollowMode(marco);

	marco2 = new Marco(shader, Vector2(400, 300), Vector2(1.5f, 1.5f));

	background = new Sprite(shader, L"Background/FinalFightStage.png");
	background->Position(400, 300);
	background->Scale(2.5f, 2.5f);

	perFrame = new PerFrame(shader);
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(background);
	SafeDelete(marco);
	SafeDelete(marco2);
	SafeDelete(perFrame);
}

void Update()
{
	perFrame->Update();
	background->Update();
	marco->Update();
	marco2->Update();
}

void Render()
{
	perFrame->Render();
	background->Render();
	marco->Render();
	marco2->Render();
}

void PostRender()
{
	RECT rect = { 0, 0, 800, 200 };
	wstring text = L"FPS : " + to_wstring(ImGui::GetIO().Framerate);
	DirectWrite::RenderText(text, rect);
}