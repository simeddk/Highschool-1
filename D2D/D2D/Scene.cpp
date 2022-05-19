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

	marco = new Marco(shader, Vector2(100, 140), Vector2(2.5f, 2.5f));
	background = new Sprite(shader, L"Background/FinalFightStage.png");
	background->Position(400, 300);
	background->Scale(2.5f, 2.5f);
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(background);
	SafeDelete(marco);
}

void Update()
{
	static float speed = 200;
	ImGui::SliderFloat("Camera Speed", (float*)&speed, 100, 1000);
	
	Freedom* freedom = dynamic_cast<Freedom*>(Context::Get()->GetCamera());
	if (freedom != nullptr)
		freedom->Speed(speed);

	background->Update();
	marco->Update();
}

void Render()
{
	background->Render();
	marco->Render();
}