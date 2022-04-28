#include "stdafx.h"
#include "Systems/Device.h"
#include "Objects/Rect.h"
#include "Objects/MovableRect.h"

Shader* shader = nullptr;
Matrix V, P;

struct Vertex
{
	Vector3 Position;
	Vector2 Uv; //TexCoord
} vertices[6];

ID3D11Buffer* vertexBuffer = nullptr;
ID3D11ShaderResourceView* srv = nullptr;

void InitScene()
{
	shader = new Shader(L"03_Texture.fx");

	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = Vector3(+0.5f, +0.5f, 0.0f);

	vertices[0].Uv = Vector2(0, 1);
	vertices[1].Uv = Vector2(0, 0);
	vertices[2].Uv = Vector2(1, 1);
	vertices[3].Uv = Vector2(1, 1);
	vertices[4].Uv = Vector2(0, 0);
	vertices[5].Uv = Vector2(1, 0);

	/*vertices[0].Uv = Vector2(0.5f, 1);
	vertices[1].Uv = Vector2(0.5f, 0);
	vertices[2].Uv = Vector2(1, 1);
	vertices[3].Uv = Vector2(1, 1);
	vertices[4].Uv = Vector2(0.5f, 0);
	vertices[5].Uv = Vector2(1, 0);*/

	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(Device->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	//Create SRV
	Check(D3DX11CreateShaderResourceViewFromFile
	(
		Device,
		L"../../_Textures/Scopedog.png",
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
	D3DXCOLOR bgcolor = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
	{
		//World
		Matrix W, S, T;
		D3DXMatrixScaling(&S, 380, 300, 1);
		D3DXMatrixTranslation(&T, 500, 350, 0);
		W = S * T;

		//View
		Vector3 eye = Vector3(0, 0, 0);
		Vector3 at = Vector3(0, 0, 1);
		Vector3 up = Vector3(0, 1, 0);
		D3DXMatrixLookAtLH(&V, &eye, &(eye + at), &up);

		//Projection
		D3DXMatrixOrthoOffCenterLH(&P, 0.f, (float)Width, 0, (float)Height, -1.f, +1.f);
		
		//SetParams
		shader->AsMatrix("World")->SetMatrix(W);
		shader->AsMatrix("View")->SetMatrix(V);
		shader->AsMatrix("Projection")->SetMatrix(P);

		shader->AsSRV("TextureMap")->SetResource(srv);

		//Pass Test
		static UINT pass = 0;
		ImGui::SliderInt("Pass", (int*)&pass, 0, 3);
		
		if (pass == 3)
		{
			static UINT filter = 0;
			ImGui::SliderInt("Filter", (int*)&filter, 0, 1);
			shader->AsScalar("Filter")->SetInt(filter);
		}

		//DrawCall
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		shader->Draw(0, pass, 6);
	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}