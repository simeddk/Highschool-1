#include "stdafx.h"
#include "S04_ObbDemo.h"
#include "Objects/Marco.h"
#include "Objects/Fire.h"

S04_ObbDemo::S04_ObbDemo()
{
	shader = new Shader(L"04_Sprite.fx");
	
	marco = new Marco(shader, Vector2(170, 100), Vector2(2.5f, 2.5f));
	fire = new Fire(shader, Vector2(350, 170), Vector2(1.5f, 1.5f));
}

S04_ObbDemo::~S04_ObbDemo()
{
	SafeDelete(shader);
	SafeDelete(marco);
	SafeDelete(fire);
}

void S04_ObbDemo::Update()
{
	const char* objectNames[] = { "Marco", "Fire" };
	static int selected;
	ImGui::Combo("Gizmo", &selected, objectNames, 2);
	if (selected == 0)
	{
		marco->EnableGizmo();
		fire->DisableGizmo();
	}
	else
	{
		marco->DisableGizmo();
		fire->EnableGizmo();
	}

	bool bObb = Collider::Obb(marco->GetSprite(), fire->GetSprite());
	bObb ? marco->GetCollider()->SetHit() : marco->GetCollider()->SetMiss();
	bObb ? fire->GetCollider()->SetHit() : fire->GetCollider()->SetMiss();

	marco->Update();
	fire->Update();
}

void S04_ObbDemo::Render()
{
	marco->Render();
	fire->Render();
}