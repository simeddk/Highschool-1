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
	//View
	camera->Update();

	//Projection
	D3DXMatrixOrthoOffCenterLH
	(
		&projection,			//out
		(float)Width * -0.5f,	//left
		(float)Width * +0.5f,	//right
		(float)Height * -0.5f,	//bottom
		(float)Height * +0.5f,	//top
		-1.f,					//zNear
		+1.f					//zFar
	);
	
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
