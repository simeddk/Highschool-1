#include "stdafx.h"
#include "Device.h"
#include "Objects/Rect.h"

Shader* shader = nullptr;
Matrix V, P;

Rect* rect = nullptr;
Rect* rect2 = nullptr;

void InitScene()
{
	shader = new Shader(L"02_World.fx");

	rect = new Rect(shader);
	rect->Position((float)Width * 0.5f, (float)Height * 0.5f);
	rect->Scale((float)Width, (float)Height);
	rect->Pass(1);

	rect2 = new Rect(shader, Vector2(500, 500), Vector2(50, 50), Color(1, 0, 0, 1));
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(rect);
	SafeDelete(rect2);
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

	//Pass Test
	static bool bCheck = true;
	ImGui::Checkbox("Use Gradiant", &bCheck);
	bCheck ? rect->Pass(1) : rect->Pass(0);

	rect->Update(V, P);
	rect2->Update(V, P);
}

void Render()
{
	D3DXCOLOR bgcolor = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
	{
		rect->Render();
		rect2->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
	
}