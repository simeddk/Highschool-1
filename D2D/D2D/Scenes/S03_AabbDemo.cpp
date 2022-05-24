#include "stdafx.h"
#include "S03_AabbDemo.h"
#include "Objects/Marco.h"
#include "Objects/Marker.h"
#include "Objects/Fire.h"

S03_AabbDemo::S03_AabbDemo()
{
	shader = new Shader(L"04_Sprite.fx");
	
	marco = new Marco(shader, Vector2(170, 100), Vector2(2.5f, 2.5f));
	marker = new Marker(shader, Vector2(250, 250));
	fire = new Fire(shader, Vector2(350, 170), Vector2(1.5f, 1.5f));
}

S03_AabbDemo::~S03_AabbDemo()
{
	SafeDelete(shader);
	SafeDelete(marco);
	SafeDelete(marker);
	SafeDelete(fire);
}

void S03_AabbDemo::Update()
{
	bool bAabb = Collider::Aabb(marco->GetWorld(), marker->Position());
	ImGui::LabelText("Matrix vs Position", "%d", bAabb);
	bAabb ? marco->GetCollider()->SetHit() : marco->GetCollider()->SetMiss();

	bool bAabb2 = Collider::Aabb(marco->GetWorld(), fire->GetWorld());
	ImGui::LabelText("Matrix vs Matrix", "%d", bAabb2);
	bAabb2 ? fire->GetCollider()->SetHit() : fire->GetCollider()->SetMiss();

	Vector2 firePosition = fire->Position();
	ImGui::SliderFloat2("Fire Position", firePosition, -400, 400);
	fire->Position(firePosition);

	Vector2 fireScale = fire->Scale();
	ImGui::SliderFloat2("Fire Scale", fireScale, 1, 10);
	fire->Scale(fireScale);

	marco->Update();
	marker->Update();
	fire->Update();
}

void S03_AabbDemo::Render()
{
	marco->Render();
	marker->Render();
	fire->Render();
}