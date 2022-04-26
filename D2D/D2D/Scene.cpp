#include "stdafx.h"
#include "Device.h"
#include "Objects/Rect.h"

Shader* shader = nullptr;
Matrix V, P;

Rect* rect = nullptr;

void InitScene()
{
	shader = new Shader(L"02_World.fx");

	rect = new Rect(shader);
	rect->Position(200, 500);
	rect->Scale(100, 100);
	rect->Color(1, 0, 0, 1);
}

void DestroyScene()
{
	SafeDelete(shader);
	SafeDelete(rect);
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

	rect->Update(V, P);

}

void Render()
{
	D3DXCOLOR bgcolor = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
	{
		rect->Render();
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
	
}