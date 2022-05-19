#include "stdafx.h"
#include "Context.h"

Context* Context::instance = nullptr;

Context::Context()
{
	camera = new Freedom();
}

Context::~Context()
{
	SafeRelease(viewProjectionBuffer);
	
	SafeDelete(camera);
}

void Context::Create()
{
	assert(instance == nullptr);
	instance = new Context();
}

void Context::Delete()
{
	SafeDelete(instance);
}

Context* Context::Get()
{
	assert(instance != nullptr);
	return instance;
}


void Context::SetShader(Shader* shader)
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

void Context::Update()
{
	camera->Update();
	desc.View = camera->View();

	//Projection
	D3DXMatrixOrthoOffCenterLH(&desc.Projection, 0.f, (float)Width, 0, (float)Height, -1.f, +1.f);
}


void Context::Render()
{
	if (shader == nullptr) return;

	D3D11_MAPPED_SUBRESOURCE subResource;
	DeviceContext->Map(viewProjectionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy(subResource.pData, &desc, sizeof(ViewProjectionDesc));
	}
	DeviceContext->Unmap(viewProjectionBuffer, 0);

	sViewProjectionBuffer->SetConstantBuffer(viewProjectionBuffer);
}