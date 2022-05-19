#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background_Mario.h"
#include "Objects/Marco.h"

Shader* shader = nullptr;
Marco* marco = nullptr;
Marco* marco2 = nullptr;
Sprite* background = nullptr;

void InitScene()
{
	shader = new Shader(L"04_Sprite.fx");
	Context::Get()->SetShader(shader);

	marco = new Marco(shader, Vector2(100, 140), Vector2(2.5f, 2.5f));
	Context::Get()->SetFollowMode(marco);

	marco2 = new Marco(shader, Vector2(400, 300), Vector2(1.5f, 1.5f));

	background = new Sprite(shader, L"Background/FinalFightStage.png");
	background->Position(400, 300);
	background->Scale(2.5f, 2.5f);
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(background);
	SafeDelete(marco);
	SafeDelete(marco2);
}

void Update()
{
	//프리덤 카메라 속도 테스트
	//static float speed = 200;
	//ImGui::SliderFloat("Camera Speed", (float*)&speed, 100, 1000);
	//
	//Freedom* freedom = dynamic_cast<Freedom*>(Context::Get()->GetCamera());
	//if (freedom != nullptr)
	//	freedom->Speed(speed);

	//빨로우 포커스 체인지

	Follow* follow = dynamic_cast<Follow*>(Context::Get()->GetCamera());
	if (follow != nullptr)
	{
		if (Key->Down(VK_F1))
			follow->ChangeFocus(marco);
		else if (Key->Down(VK_F2))
			follow->ChangeFocus(marco2);
	}

	background->Update();
	marco->Update();
	marco2->Update();
}

void Render()
{
	background->Render();
	marco->Render();
	marco2->Render();
}