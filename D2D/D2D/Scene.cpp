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
	static Vector2 test;
	ImGui::SliderFloat2("Test", test, 1, 100);
	
	static bool bCheck;
	ImGui::Checkbox("Check", &bCheck);

	static Color color;
	ImGui::ColorEdit3("Color", color);

	ImGui::Text("%.f, %.2f", background->Position().x, background->Position().y);

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

void PostRender()
{
	static Color fontColor = Color(1, 1, 1, 1);
	ImGui::ColorEdit4("Font Color", fontColor);

	RECT rect = { 0, 0, 800, 200 };
	wstring text = L"키스의 고유 조건은 입술끼리 만나야 하고 특별한 기술은 필요치 않다..";
	DirectWrite::SetFontColor(fontColor);
	DirectWrite::SetFontSize(17);
	DirectWrite::RenderText(text, rect);

	rect.top += 25;
	rect.bottom += 25;
	text = L"FPS : " + to_wstring(ImGui::GetIO().Framerate);
	DirectWrite::SetFontColor(Color(1, 0, 0, 1));
	DirectWrite::RenderText(text, rect);
}