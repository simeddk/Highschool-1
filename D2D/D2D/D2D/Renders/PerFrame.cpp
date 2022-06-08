#include "stdafx.h"
#include "PerFrame.h"

PerFrame::PerFrame(Shader* shader)
{
	this->shader = shader;

	//Create ConstantBuffer
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(ViewProjectionDesc);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	Check(Device->CreateBuffer(&desc, nullptr, &viewProjectionBuffer));

	sViewProjectionBuffer = this->shader->AsConstantBuffer("CB_PerFrame");
}

PerFrame::~PerFrame()
{
	SafeRelease(viewProjectionBuffer);
}

void PerFrame::Update()
{
	desc.View = Context::Get()->GetView();
	desc.Projection = Context::Get()->GetProjection();
}

void PerFrame::Render()
{
	CheckNull(shader);

	D3D11_MAPPED_SUBRESOURCE subResource;
	DeviceContext->Map(viewProjectionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy(subResource.pData, &desc, sizeof(ViewProjectionDesc));
	}
	DeviceContext->Unmap(viewProjectionBuffer, 0);

	sViewProjectionBuffer->SetConstantBuffer(viewProjectionBuffer);
}
