#include "stdafx.h"
#include "Device.h"

Shader* shader = nullptr;

ID3D11Buffer* vertexBuffer = nullptr;
ID3D11Buffer* indexBuffer = nullptr;
ID3D11RasterizerState* wireFrameMode = nullptr;

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXCOLOR Color;
};

Vertex vertices[4];
UINT indices[6];

void InitScene()
{
	shader = new Shader(L"01_Effect.fx");

	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); //좌하
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f); //좌상
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f); //우하
	vertices[3].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f); //우상
	
	vertices[0].Color = D3DXCOLOR(1, 0, 0, 1); //R
	vertices[1].Color = D3DXCOLOR(0, 1, 0, 1); //G
	vertices[2].Color = D3DXCOLOR(0, 0, 1, 1); //B
	vertices[3].Color = D3DXCOLOR(0, 1, 1, 1); //C

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

	//Create RasterizerState(WireFrame)
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_WIREFRAME;
		desc.CullMode = D3D11_CULL_BACK;
		HRESULT hr = Device->CreateRasterizerState(&desc, &wireFrameMode);
		assert(SUCCEEDED(hr));
	}
	
}

void DestroyScene()
{
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
	SafeRelease(wireFrameMode);
}

bool bWireFrameMode = false;
D3DXCOLOR color = D3DXCOLOR(0, 1, 0, 1);
void Update()
{
	ImGui::Text("%s", "Hello World");
	ImGui::Checkbox("WireFrame", &bWireFrameMode);
	ImGui::ColorEdit3("Color", (float*)color);
	//ImGui::Text("%f, %f, %f", color[0], color[1], color[2]);
	ImGui::Text("%f, %f, %f", color.r, color.g, color.b);

	shader->AsVector("Color")->SetFloatVector(color);

	if (Key->Toggle('1')) //Toggle
		bWireFrameMode = !bWireFrameMode;
	
	//모든 정점 이동하기
	if (Key->Press('A'))
	{
		for (int i = 0; i < ARRAYSIZE(vertices); i++)
			vertices[i].Position.x -= 1e-4f;
	}
	else if (Key->Press('D'))
	{
		for (int i = 0; i < ARRAYSIZE(vertices); i++)
			vertices[i].Position.x += 1e-4f;
	}

	if (Key->Press('S'))
	{
		for (int i = 0 ; i < ARRAYSIZE(vertices); i++)
			vertices[i].Position.y -= 1e-4f;
	}
	else if (Key->Press('W'))
	{
		for (int i = 0; i < ARRAYSIZE(vertices); i++)
			vertices[i].Position.y += 1e-4f;
	}

	D3D11_MAPPED_SUBRESOURCE subResouce;
	DeviceContext->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResouce);
	{
		memcpy(subResouce.pData, vertices, sizeof(Vertex) * ARRAYSIZE(vertices));
	}
	DeviceContext->Unmap(vertexBuffer, 0);
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

		DeviceContext->RSSetState(bWireFrameMode ? wireFrameMode : nullptr);

		shader->DrawIndexed(0, 0, 6);
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
	
}