#include "stdafx.h"
#include "Rect.h"

Rect::Rect(Shader* shader)
	: shader(shader)
	, position(0, 0)
	, scale(1, 1)
	, color(1, 1, 1, 1)
	, pass(0)
{
	Initialize();
}

Rect::Rect(Shader* shader, Vector2 position, Vector2 scale, D3DXCOLOR color)
	: shader(shader)
	, position(position)
	, scale(scale)
	, color(color)
	, pass(0)
{
	Initialize();
}

void Rect::Initialize()
{
	CreateBuffer();

	D3DXMatrixIdentity(&world);

	sWorld = shader->AsMatrix("World");
	sColor = shader->AsVector("Color");

	perFrame = new PerFrame(shader);
}

void Rect::CreateBuffer()
{
	Vertex vertices[4];

	//Vertex Subresource Data
	{
		vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
		vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
		vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);

		vertices[0].Color = D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f);
		vertices[1].Color = D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f);
		vertices[2].Color = D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f);
		vertices[3].Color = D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f);
	}

	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(Vertex) * 4;
		desc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(Device->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	//Index SubResource Data
	UINT indices[6] = { 0, 1, 2, 2, 1, 3 };

	//Create IndexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(Device->CreateBuffer(&desc, &subResource, &indexBuffer));
	}
}


Rect::~Rect()
{
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
	SafeDelete(perFrame);
}

void Rect::Update()
{
	perFrame->Update();
}

void Rect::Render()
{
	ApplyTo();

	perFrame->Render();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->DrawIndexed(0, pass, 6);
}

void Rect::ApplyTo()
{
	Matrix S, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
	D3DXMatrixTranslation(&T, position.x, position.y, 0.0f);
	world = S * T;

	sWorld->SetMatrix(world);
	sColor->SetFloatVector(color);
}

void Rect::Position(float x, float y)
{
	Position(Vector2(x, y));
}

void Rect::Position(Vector2& vec)
{
	position = vec;
}

void Rect::Scale(float x, float y)
{
	Scale(Vector2(x, y));
}

void Rect::Scale(Vector2& vec)
{
	scale = vec;
}

void Rect::Color(float r, float g, float b, float a)
{
	Color(D3DXCOLOR(r, g, b, a));
}

void Rect::Color(D3DXCOLOR& color)
{
	this->color = color;
}

void Rect::Pass(UINT val)
{
	pass = val;
}




