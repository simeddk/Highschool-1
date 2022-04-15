#include "Device.h"

ID3D11Buffer* vertexBuffer = nullptr;
ID3D11InputLayout* inputLayout = nullptr;

struct Vertex
{
	D3DXVECTOR3 Position;
};

void InitScene()
{
	Vertex vertices[4];

	//Line1
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);

	//Line2
	vertices[2].Position = D3DXVECTOR3(-0.5f, +0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(+0.5f, -0.5f, 0.0f);

	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &subResource, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	//Create InputLayout
	{
		D3D11_INPUT_ELEMENT_DESC desc =
		{
			"POSITION",						//SemanticName;
			0,								//SemanticIndex;
			DXGI_FORMAT_R32G32B32_FLOAT,	//Format;
			0,								//InputSlot;
			0,								//AlignedByteOffset;
			D3D11_INPUT_PER_VERTEX_DATA,	//InputSlotClass;
			0,								//InstanceDataStepRate;
		};
		

		HRESULT hr = Device->CreateInputLayout
		(
			&desc,
			1,  
			VsBlob->GetBufferPointer(),
			VsBlob->GetBufferSize(),
			&inputLayout
		);
		assert(SUCCEEDED(hr));
	}
	
}

void DestroyScene()
{
	inputLayout->Release();
	vertexBuffer->Release();
}

D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
void Update()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		topology = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
}

void Render()
{
	D3DXCOLOR bgcolor = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(topology);
		DeviceContext->IASetInputLayout(inputLayout);

		DeviceContext->Draw(4, 0);
	}
	SwapChain->Present(0, 0);
}