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
	static bool bOrtho = true;
	ImGui::Checkbox("Use Ortho Projection", &bOrtho);

	if (bOrtho)
	{
		static Vector2 horizontal = Vector2(0, (float)Width);
		static Vector2 vertical = Vector2(0, (float)Height);

		ImGui::SliderFloat2("Horizontal", horizontal, -800, 800);
		ImGui::SliderFloat2("Vertical", vertical, -800, 800);

		D3DXMatrixOrthoOffCenterLH
		(
			&projection, //out
			horizontal.x, //left
			horizontal.y, //right
			vertical.x, //bottom
			vertical.y, //top
			-1.f, //zNear
			+1.f //zFar
		);
	}
	else
	{
		static float fov = 0.25f;
		static float n = 0.0f;
		static float f = 255.f;
		ImGui::SliderFloat("FOV", &fov, 0.001f, 1.0f);
		ImGui::SliderFloat("Depth", &camera->Depth(), -100, -1000);

		float aspect = (float)Width / (float)Height;
		D3DXMatrixPerspectiveFovLH(&projection, fov * D3DX_PI, aspect, n, f);
	}


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
