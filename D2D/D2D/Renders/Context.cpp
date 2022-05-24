#include "stdafx.h"
#include "Context.h"
#include "Viewer/IFollow.h"

Context* Context::instance = nullptr;

Context::Context()
{
	camera = new Freedom();
	D3DXMatrixIdentity(&projection);
}

Context::~Context()
{
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

void Context::Update()
{
	camera->Update();

	//Projection
	D3DXMatrixOrthoOffCenterLH(&projection, 0.f, (float)Width, 0, (float)Height, -1.f, +1.f);
}

const Matrix& Context::GetView()
{
	return camera->View();
}

const Matrix& Context::GetProjection()
{
	return projection;
}

void Context::SetFollowMode(IFollow* focusObject)
{
	SafeDelete(camera);
	camera = new Follow(focusObject);
}

void Context::SetFreedomMode()
{
	SafeDelete(camera);
	camera = new Freedom();
}
