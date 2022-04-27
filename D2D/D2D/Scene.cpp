#include "stdafx.h"
#include "Device.h"
#include "Objects/Rect.h"
#include "Objects/MovableRect.h"

Shader* shader = nullptr;
Matrix V, P;

Rect* rect = nullptr;
Rect* rect2 = nullptr;
MovableRect* movable = nullptr;

void InitScene()
{
	shader = new Shader(L"02_World.fx");

	rect = new Rect(shader);
	rect->Position((float)Width * 0.5f, (float)Height * 0.5f);
	rect->Scale((float)Width, (float)Height);
	rect->Pass(1);

	rect2 = new Rect(shader, Vector2(500, 500), Vector2(50, 50), Color(1, 0, 0, 1));

	movable = new MovableRect(shader);
	movable->Scale(100, 100);
	movable->Position((float)Width * 0.5f, movable->Scale().y * 0.5f);
	movable->Color(0.463f, 0.769f, 0.682f);
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(rect);
	SafeDelete(rect2);
	SafeDelete(movable);
}


void Update()
{
	//View Matrix
	Vector3 eye = Vector3(0, 0, 0);
	Vector3 at = Vector3(0, 0, 1);
	Vector3 up = Vector3(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &(eye + at), &up);

	//Projection Matrix
	D3DXMatrixOrthoOffCenterLH(&P, 0.f, (float)Width, 0, (float)Height, -1.f, +1.f);

	//MoveSpeed Test
	float moveSpeed = movable->MoveSpeed();
	ImGui::SliderFloat("MoveSpeed", &moveSpeed, 0.0001f, 0.5f);
	movable->MoveSpeed(moveSpeed);

	//FPS
	ImGui::Text("%.2f", ImGui::GetIO().Framerate);

	rect->Update(V, P);
	rect2->Update(V, P);

	if (Key->Press('A') || Key->Press(VK_LEFT))
		movable->MoveLeft();
	else if (Key->Press('D') || Key->Press(VK_RIGHT))
		movable->MoveRight();

	movable->Update(V, P);

}

void Render()
{
	D3DXCOLOR bgcolor = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
	{
		rect->Render();
		rect2->Render();
		movable->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
	
}