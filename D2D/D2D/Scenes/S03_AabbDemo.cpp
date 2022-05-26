#include "stdafx.h"
#include "S03_AabbDemo.h"
#include "Objects/Marco.h"
#include "Objects/Marker.h"
#include "Objects/Fire.h"
#include "Renders/Gizmo.h"

S03_AabbDemo::S03_AabbDemo()
{
	shader = new Shader(L"04_Sprite.fx");
	
	marco = new Marco(shader, Vector2(170, 100), Vector2(2.5f, 2.5f));
	marker = new Marker(shader, Vector2(250, 250));
	fire = new Fire(shader, Vector2(350, 170), Vector2(1.5f, 1.5f));

	D3DXMatrixIdentity(&trigger);
	triggerCollider = new Collider();

	gizmo = new Gizmo();
}

S03_AabbDemo::~S03_AabbDemo()
{
	SafeDelete(shader);
	SafeDelete(marco);
	SafeDelete(marker);
	SafeDelete(fire);
	SafeDelete(triggerCollider);
	SafeDelete(gizmo);
}

void S03_AabbDemo::Update()
{
	bool bAabb = Collider::Aabb(marco->GetWorld(), marker->Position());
	ImGui::LabelText("Matrix vs Position", "%d", bAabb);
	bAabb ? marco->GetCollider()->SetHit() : marco->GetCollider()->SetMiss();

	bool bAabb2 = Collider::Aabb(marco->GetWorld(), fire->GetWorld());
	ImGui::LabelText("Matrix vs Matrix", "%d", bAabb2);
	bAabb2 ? fire->GetCollider()->SetHit() : fire->GetCollider()->SetMiss();

	ImGui::SliderFloat2("Fire Position", fire->Position(), -400, 400);
	ImGui::SliderFloat2("Fire Scale", fire->Scale(), 1, 10);

	Matrix t, s;
	D3DXMatrixScaling(&s, 200, 40, 1);
	D3DXMatrixTranslation(&t, 300, 300, 0);
	trigger = s* t;
	triggerCollider->Update(trigger);

	bool bAabb3 = Collider::Aabb(marco->GetWorld(), trigger);
	ImGui::LabelText("Matrix vs Trigger", "%s", bAabb3 ? "On" : "Off");
	bAabb3 ? triggerCollider->SetHit() : triggerCollider->SetMiss();
	bAabb3 ? fire->Stop() : fire->Play();

	marco->Update();
	marker->Update();
	fire->Update();

	Vector2 scale, translate;
	Vector3 rotation;
	gizmo->Set(marco->GetSprite(), &scale, &rotation, &translate, 1);
	ImGui::LabelText("Test", "%.2f,  %.2f", translate.x, translate.y);
	marco->Position(translate);
	marco->Scale(scale);
	marco->Rotation(rotation);
}

void S03_AabbDemo::Render()
{
	marco->Render();
	marker->Render();
	fire->Render();
	triggerCollider->Render();
}