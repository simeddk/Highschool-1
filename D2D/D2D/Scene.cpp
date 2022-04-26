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

Matrix W1, W2;
Matrix V, P;

void InitScene()
{
	shader = new Shader(L"02_World.fx");

	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f); //ÁÂÇÏ
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f); //ÁÂ»ó
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f); //¿ìÇÏ
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f); //¿ì»ó
	
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

	//View Matrix
	Vector3 eye = Vector3(0, 0, 0);
	Vector3 at = Vector3(0, 0, 1);
	Vector3 up = Vector3(0, 1, 0);
	D3DXMatrixLookAtLH(&V, &eye, &(eye + at), &up);

	//Projection Matrix
	D3DXMatrixOrthoOffCenterLH(&P, 0.f, (float)Width, 0, (float)Height, -1.f, +1.f);

}

void DestroyScene()
{
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}



void Update()
{
	static Vector2 position1 = Vector2(300, 400);
	static Vector2 position2 = Vector2(600, 400);

	//World Matrix 1
	{
		if (Key->Press('A'))
			position1.x -= 0.1f;
		else if (Key->Press('D'))
			position1.x += 0.1f;

		if (Key->Press('S'))
			position1.y -= 0.1f;
		else if (Key->Press('W'))
			position1.y += 0.1f;

		Matrix S, T;
		D3DXMatrixScaling(&S, 100.f, 100.f, 1.f);
		D3DXMatrixTranslation(&T, position1.x, position1.y, 0.0f);
		W1 = S * T;
	}

	//World Matrix 2
	{
		if (Key->Press(VK_LEFT))
			position2.x -= 0.1f;
		else if (Key->Press(VK_RIGHT))
			position2.x += 0.1f;

		if (Key->Press(VK_DOWN))
			position2.y -= 0.1f;
		else if (Key->Press(VK_UP))
			position2.y += 0.1f;

		Matrix S, T;
		D3DXMatrixScaling(&S, 50.f, 75.f, 1.f);
		D3DXMatrixTranslation(&T, position2.x, position2.y, 0.0f);
		W2 = S * T;
	}

	//Set Parameters
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

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

		shader->AsMatrix("World")->SetMatrix(W1);
		shader->AsVector("Color")->SetFloatVector(Color(0, 1, 0, 1));
		shader->DrawIndexed(0, 0, 6);

		shader->AsMatrix("World")->SetMatrix(W2);
		shader->AsVector("Color")->SetFloatVector(Color(0, 0, 1, 1));
		shader->DrawIndexed(0, 0, 6);
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
	
}