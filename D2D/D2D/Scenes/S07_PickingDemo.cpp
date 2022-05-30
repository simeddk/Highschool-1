#include "stdafx.h"
#include "S07_PickingDemo.h"
#include "Objects/Marker.h"
#include "Objects/Rect.h"

S07_PickingDemo::S07_PickingDemo()
{
	shader = new Shader(L"04_Sprite.fx");
	background = new Sprite(shader, L"Background/SonicStage.png");
	perFrame = new PerFrame(shader);

	rectShader = new Shader(L"05_Bounding.fx");
	rect = new Rect(rectShader, Vector2(100, 100), Vector2(100, 100));
}

S07_PickingDemo::~S07_PickingDemo()
{
	SafeDelete(shader);
	SafeDelete(background);
	SafeDelete(perFrame);

	SafeDelete(rectShader);
	SafeDelete(rect);

	for (Marker* marker : markers)
		SafeDelete(marker);
}

void S07_PickingDemo::Update()
{
	ImGui::LabelText("Mouse", "%.2f, %.2f", Mouse->Position_OnViewport().x, Mouse->Position_OnViewport().y);

	//Vector2 mouse = Mouse->Position_OnViewport();
	//mouse.x = mouse.x - (float)Width * 0.5f;
	//mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;

	//Vector2 camera = Context::Get()->GetCamera()->Position();
	//Vector2 wPosition = mouse + camera;
	Vector2 wPosition = Mouse->Position_World();
	
	if (Mouse->Down(LButton))
		markers.push_back(new Marker(shader, wPosition));

	perFrame->Update();
	background->Update();

	for (Marker* marker : markers)
		marker->Update();

	Matrix V = Context::Get()->GetView();
	Matrix P = Context::Get()->GetProjection();
	rect->Update(V, P);

	bool bPicked = true;
	bPicked &= Collider::Aabb(rect->World(), wPosition);
	bPicked &= Mouse->Press(MButton);

	Collider::Aabb(rect->World(), wPosition) ? rect->Color(1, 0, 0, 1) : rect->Color(1, 1, 1, 1);

	if (bPicked)
		rect->Position(wPosition);
}

void S07_PickingDemo::Render()
{
	perFrame->Render();
	background->Render();

	for (Marker* marker : markers)
		marker->Render();

	rect->Render();
}