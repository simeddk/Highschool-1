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

	D3DXMatrixIdentity(&W);
	D3DXMatrixIdentity(&V);
	D3DXMatrixIdentity(&P);
	
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


Vector3 position = Vector3(110, 110, 0);
void Update()
{
	//World Matrix
	{
		if (Key->Press('A'))
			position.x -= 0.1f;
		else if (Key->Press('D'))
			position.x += 0.1f;

		if (Key->Press('S'))
			position.y -= 0.1f;
		else if (Key->Press('W'))
			position.y += 0.1f;

		Matrix S, T;
		
		//Scaing
		D3DXMatrixScaling(&S, 200.f, 200.f, 1.f); //_11 = 200, _22 = 200

		//Translation
		D3DXMatrixTranslation(&T, position.x, position.y, 0.0f); //_41 = 110, _42 = 110

		W = S * T;
	}

	//15:01

	//Set Parameters
	shader->AsMatrix("World")->SetMatrix(W);
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

		shader->DrawIndexed(0, 0, 6);
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
	
}