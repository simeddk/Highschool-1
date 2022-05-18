#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Background_Mario.h"
#include "Objects/Marco.h"

Shader* shader = nullptr;
Background_Mario* background = nullptr;
Marco* marco = nullptr;
Sprite* scopeDog = nullptr;

void InitScene()
{
	shader = new Shader(L"04_Sprite.fx");
	Context::Get()->SetShader(shader);

	background = new Background_Mario(shader);
	marco = new Marco(shader, Vector2(100, 171), Vector2(2.5f, 2.5f));

	scopeDog = new Sprite(shader, L"ScopeDog.png");
	scopeDog->Position(400, 190);
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(background);
	SafeDelete(marco);
	SafeDelete(scopeDog);
}

void Update()
{
	//Yaw, Pitch, Roll
	static int selected;
	ImGui::RadioButton("Yaw", &selected, 0);
	ImGui::RadioButton("Pitch", &selected, 1);
	ImGui::RadioButton("Roll", &selected, 2);

	Vector3 rotation = scopeDog->RotationDegree();
	if (Key->Press(VK_LEFT))
	{
		switch (selected)
		{
			case 0: rotation.y -= 400.0f * Time::Delta(); break;
			case 1: rotation.x -= 400.0f * Time::Delta(); break;
			case 2: rotation.z -= 400.0f * Time::Delta(); break;
		}
	}
	else if (Key->Press(VK_RIGHT))
	{
		switch (selected)
		{
			case 0: rotation.y += 400.0f * Time::Delta(); break;
			case 1: rotation.x += 400.0f * Time::Delta(); break;
			case 2: rotation.z += 400.0f * Time::Delta(); break;
		}
	}
	scopeDog->RotationDegree(rotation);

	static bool bAutoRotation;
	ImGui::Checkbox("AutoRotation", &bAutoRotation);
	if (bAutoRotation == true)
	{
		switch (selected)
		{
			case 0: scopeDog->Rotation(0, sinf(Time::Get()->Running()) * D3DX_PI, 0); break;
			case 1: scopeDog->Rotation(sinf(Time::Get()->Running()) * D3DX_PI, 0, 0); break;
			case 2: scopeDog->Rotation(0, 0, sinf(Time::Get()->Running()) * D3DX_PI); break;
		}
	}

	//Debug - 각 축의 Degree 보기
	if (ImGui::CollapsingHeader("Rotation(Degree)", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::LabelText
		(
			"X Y Z",
			"%.2f, %.2f, %.2f",
			scopeDog->RotationDegree().x,
			scopeDog->RotationDegree().y,
			scopeDog->RotationDegree().z
		);
	}

	//Debug - Local Matrix 보기
	if (ImGui::CollapsingHeader("Local Matrix", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("%.2f, %.2f, %.2f", scopeDog->World()._11, scopeDog->World()._12, scopeDog->World()._13);
		ImGui::Text("%.2f, %.2f, %.2f", scopeDog->World()._21, scopeDog->World()._22, scopeDog->World()._23);
		ImGui::Text("%.2f, %.2f, %.2f", scopeDog->World()._31, scopeDog->World()._32, scopeDog->World()._33);
	}

	//Debug - Local Direction 보기
	if (ImGui::CollapsingHeader("Local Direction", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("%.2f, %.2f, %.2f", scopeDog->Right().x, scopeDog->Right().y, scopeDog->Right().z);
		ImGui::Text("%.2f, %.2f, %.2f", scopeDog->Up().x, scopeDog->Up().y, scopeDog->Up().z);
		ImGui::Text("%.2f, %.2f, %.2f", scopeDog->Foward().x, scopeDog->Foward().y, scopeDog->Foward().z);
	}


	background->Update();
	marco->Update();
	scopeDog->Update();
}

void Render()
{
	background->Render();
	marco->Render();
	scopeDog->Render();
}