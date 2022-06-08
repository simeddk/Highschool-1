#include "stdafx.h"
#include "S06_MouseDemo.h"


S06_MouseDemo::S06_MouseDemo()
{
	shader = new Shader(L"04_Sprite.fx");
	background = new Sprite(shader, L"Background/SonicStage.png");
	perFrame = new PerFrame(shader);
}

S06_MouseDemo::~S06_MouseDemo()
{
	SafeDelete(shader);
	SafeDelete(background);
	SafeDelete(perFrame);
}

void S06_MouseDemo::Update()
{
	if (Mouse->DoubleClick(LButton))
		MessageBox(Hwnd, L"¿Ş¹öÆ°", L"DoubleClick", MB_OK);
	if (Mouse->Up(MButton))
		MessageBox(Hwnd, L"Áß¹öÆ°", L"Up", MB_OK);

	ImGui::LabelText("OnViewport", "%.2f, %.2f", Mouse->Position_OnViewport().x, Mouse->Position_OnViewport().y);
	ImGui::LabelText("OnClient", "%.2f, %.2f", Mouse->Position_OnClient().x, Mouse->Position_OnClient().y);
	ImGui::LabelText("Wheel", "%.2f", Mouse->Wheel());
	ImGui::LabelText("Wheel_Delta", "%.2f", Mouse->Wheel_Delta());
	ImGui::LabelText("Position_Delta", "%.2f, %.2f", Mouse->Position_Delta().x, Mouse->Position_Delta().y);

	perFrame->Update();
	background->Update();
}

void S06_MouseDemo::Render()
{
	perFrame->Render();
	background->Render();
}