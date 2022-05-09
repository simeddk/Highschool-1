#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Rect.h"
#include "Objects/MovableRect.h"

Shader* shader = nullptr;

struct Vertex
{
	Vector3 Position;
	Vector2 Uv;
} vertices[4];

ID3D11Buffer* vertexBuffer = nullptr;
ID3D11Buffer* indexBuffer = nullptr;
ID3D11ShaderResourceView* srv = nullptr;

void InitScene()
{
	shader = new Shader(L"03_Texture.fx");
	Context::Get()->SetShader(shader);

	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = Vector2(0.259f, 0.744f);
	vertices[1].Uv = Vector2(0.259f, 0.533f);
	vertices[2].Uv = Vector2(0.351f, 0.744f);
	vertices[3].Uv = Vector2(0.351f, 0.533f);
	

	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(Device->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	UINT indices[] = { 0, 1, 2, 2, 1, 3 };
	//Create IndexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(Device->CreateBuffer(&desc, &subResource, &indexBuffer));
	}

	//Create SRV
	Check(D3DX11CreateShaderResourceViewFromFile
	(
		Device,
		L"../../_Textures/MarioSheet.png",
		nullptr,
		nullptr,
		&srv,
		nullptr
	));
	
}


void DestroyScene()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(srv);
}


void Update()
{
	
}

void Render()
{
	
	//World
	Matrix W, S, T;
	D3DXMatrixScaling(&S, 380, 300, 1);
	D3DXMatrixTranslation(&T, 500, 350, 0);
	W = S * T;

	//SetParams
	shader->AsMatrix("World")->SetMatrix(W);
	shader->AsSRV("TextureMap")->SetResource(srv);

	//Pass Test
	static UINT pass = 4;
	ImGui::SliderInt("Pass", (int*)&pass, 0, 4);
		
	if (pass == 3)
	{
		static UINT filter = 0;
		ImGui::SliderInt("Filter", (int*)&filter, 0, 1);
		shader->AsScalar("Filter")->SetInt(filter);
	}

	if (pass == 4)
	{
		static float time = 0;
		ImGui::SliderFloat("Time", &time, 0, 1);
		shader->AsScalar("Time")->SetFloat(sinf(time * 5.0f) * 0.5f + 0.5f);

		time = Time::Get()->Running();
		ImGui::LabelText("Elpased Time", "%.2f", time);

	}

	//DrawCall
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//shader->Draw(0, pass, 6);

	D3DXMatrixScaling(&S, 57 * 2, 77 * 2, 1);
	D3DXMatrixTranslation(&T, 800, 350, 0);
	W = S * T;
	shader->AsMatrix("World")->SetMatrix(W);
	shader->DrawIndexed(0, 3, 6);
	
	
}