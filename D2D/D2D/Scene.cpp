#include "stdafx.h"
#include "Device.h"

ID3D11Buffer* vertexBuffer = nullptr;
ID3D11InputLayout* inputLayout = nullptr;
ID3D11RasterizerState* wireFrameMode = nullptr;

struct Vertex
{
	D3DXVECTOR3 Position;
	D3DXCOLOR Color;
};
Vertex vertices[6];

void InitScene()
{
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); //좌하
	vertices[1].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f); //좌상
	vertices[2].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f); //우하
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f); //우하
	vertices[4].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f); //좌상
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f); //우상

	vertices[0].Color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); //R
	vertices[1].Color = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f); //G
	vertices[2].Color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f); //B
	vertices[3].Color = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f); //C
	vertices[4].Color = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f); //M
	vertices[5].Color = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f); //Y

	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &subResource, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	//Create InputLayout
	{
		D3D11_INPUT_ELEMENT_DESC desc[] =
		{
			{
				"POSITION",						//SemanticName;
				0,								//SemanticIndex;
				DXGI_FORMAT_R32G32B32_FLOAT,	//Format;
				0,								//InputSlot;
				0,								//AlignedByteOffset;
				D3D11_INPUT_PER_VERTEX_DATA,	//InputSlotClass;
				0								//InstanceDataStepRate;
			},
			{
				"COLOR",						//SemanticName;
				0,								//SemanticIndex;
				DXGI_FORMAT_R32G32B32_FLOAT,	//Format;
				0,								//InputSlot;
				12,								//AlignedByteOffset;
				D3D11_INPUT_PER_VERTEX_DATA,	//InputSlotClass;
				0								//InstanceDataStepRate;
			}
		};
		

		HRESULT hr = Device->CreateInputLayout
		(
			desc,
			2,  
			VsBlob->GetBufferPointer(),
			VsBlob->GetBufferSize(),
			&inputLayout
		);
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
	inputLayout->Release();
	vertexBuffer->Release();
}

bool bWireFrameMode = false;
void Update()
{
	if (Key->Toggle('1')) //Toggle
		bWireFrameMode = !bWireFrameMode;
	
	if (Key->Down(VK_SPACE))
		MessageBox(Hwnd, L"스페이스바가 눌림", L"키보드 테스트", MB_OK);

	if (Key->Up(VK_RETURN))
		MessageBox(Hwnd, L"엔터키를 눌렀다 뗌", L"키보드 테스트", MB_OK);

	//[0]정점 이동하기
	if (Key->Press('A'))
		vertices[0].Position.x -= 1e-4f;
	else if (Key->Press('D'))
		vertices[0].Position.x += 1e-4f;

	if (Key->Press('S'))
		vertices[0].Position.y -= 1e-4f;
	else if (Key->Press('W'))
		vertices[0].Position.y += 1e-4f;

	DeviceContext->UpdateSubresource
	(
		vertexBuffer,
		0, nullptr, vertices, sizeof(Vertex) * 6, 0
	);

}

void Render()
{
	D3DXCOLOR bgcolor = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DeviceContext->IASetInputLayout(inputLayout);

		DeviceContext->RSSetState(bWireFrameMode ? wireFrameMode : nullptr);

		DeviceContext->Draw(6, 0);
	}
	SwapChain->Present(0, 0);
}