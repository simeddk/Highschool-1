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
	Vector3 rotation = scopeDog->RotationDegree();
	if (Key->Press(VK_LEFT))
	{
		rotation.y -= 400.0f * Time::Delta();
	}
	else if (Key->Press(VK_RIGHT))
	{
		rotation.y += 400.0f * Time::Delta();
	}
	scopeDog->RotationDegree(rotation);

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