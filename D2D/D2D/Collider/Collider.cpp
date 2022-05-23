#include "stdafx.h"
#include "Collider.h"

Collider::Collider()
{
	D3DXMatrixIdentity(&world);

	shader = new Shader(L"05_Bounding.fx");
	sWorld = shader->AsMatrix("World");
	sColor = shader->AsVector("Color");

	perFrame = new PerFrame(shader);

	//Create VertexBuffer
	{
		Vertex vertices[5];
		vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
		vertices[2].Position = Vector3(+0.5f, +0.5f, 0.0f);
		vertices[3].Position = Vector3(+0.5f, -0.5f, 0.0f);
		vertices[4].Position = Vector3(-0.5f, -0.5f, 0.0f);

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * 5;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(Device->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}
}

Collider::~Collider()
{
	SafeDelete(shader);
	SafeDelete(perFrame);

	SafeRelease(vertexBuffer);
}

void Collider::Update(Matrix& world)
{
	this->world = world;
	perFrame->Update();
}

void Collider::Render()
{
	perFrame->Render();

	sWorld->SetMatrix(world);
	sColor->SetFloatVector(bHitted ? Color(1, 0, 0, 1) : Color(0, 1, 0, 1));

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	shader->Draw(0, 0, 5);
}
