#include "stdafx.h"
#include "Device.h"

Shader* shader = nullptr;

ID3D11Buffer* vertexBuffer = nullptr;
ID3D11Buffer* indexBuffer = nullptr;

struct Vertex
{
	Vector3 Position;
	Color Color;
};

Vertex vertices[4];
UINT indices[6];

Matrix W, V, P;

void InitScene()
{
	shader = new Shader(L"02_World.fx");

	vertices[0].Position = Vector3(-100.0f, -100.0f, 0.0f); //좌하
	vertices[1].Position = Vector3(-100.0f, +100.0f, 0.0f); //좌상
	vertices[2].Position = Vector3(+100.0f, -100.0f, 0.0f); //우하
	vertices[3].Position = Vector3(+100.0f, +100.0f, 0.0f); //우상
	
	vertices[0].Color = Color(1, 0, 0, 1); //R
	vertices[1].Color = Color(0, 1, 0, 1); //G
	vertices[2].Color = Color(0, 0, 1, 1); //B
	vertices[3].Color = Color(0, 1, 1, 1); //C

	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &subResource, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 1;
	indices[5] = 3;

	//Create IndexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		HRESULT hr = Device->CreateBuffer(&desc, &subResource, &indexBuffer);
		assert(SUCCEEDED(hr));
	}

	D3DXMatrixIdentity(&W);
	D3DXMatrixIdentity(&V);
	D3DXMatrixIdentity(&P);
	
	//World Matrix
	W._41 = 110.f, W._42 = 110.f;

	//View Matrix
	Vector3 eye = Vector3(0, 0, 0);
	Vector3 at = Vector3(0, 0, 1);
	Vector3 up = Vector3(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &(eye + at), &up);

	//Projection Matrix
	D3DXMatrixOrthoOffCenterLH(&P, 0.f, (float)Width, 0, (float)Height, -1.f, +1.f);

	//Set Parameters
	shader->AsMatrix("World")->SetMatrix(W);
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

}

void DestroyScene()
{
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

D3DXCOLOR color = D3DXCOLOR(0, 1, 0, 1);
Vector3 position = Vector3(110, 110, 0);
void Update()
{
	//World Matrix를 이용한 이동 테스트
	{
		if (Key->Press('A'))
			position.x -= 0.1f;
		else if (Key->Press('D'))
			position.x += 0.1f;

		if (Key->Press('S'))
			position.y -= 0.1f;
		else if (Key->Press('W'))
			position.y += 0.1f;

		D3DXMatrixTranslation(&W, position.x, position.y, 0.0f);
		shader->AsMatrix("World")->SetMatrix(W);
	}

	//View 테스트
	{
		ImGui::SliderFloat("Exe X", &V._41, -800, +800);
		ImGui::SliderFloat("Exe Z", &V._43, 0, 2000);
		shader->AsMatrix("View")->SetMatrix(V);

		ImGui::LabelText("Position", "%.2f, %.2f", position.x, position.y);
	}

	//Projection 테스트
	{
		float fov = 3.141592f * 0.5f;
		float aspect = (float)Width / (float)Height;

		D3DXMatrixPerspectiveFovLH(&P, fov, aspect, 0, 1000);
		shader->AsMatrix("Projection")->SetMatrix(P);
	}

}

void Render()
{
	D3DXCOLOR bgcolor = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		shader->DrawIndexed(0, 0, 6);
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
	
}