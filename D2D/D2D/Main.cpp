#include "stdafx.h"
#include "Systems/Device.h"

#include "Scenes/Scene.h"
#include "Scenes/S01_Scene01Demo.h"
#include "Scenes/S02_Scene02Demo.h"
#include "Scenes/S03_AabbDemo.h"
#include "Scenes/S04_ObbDemo.h"
#include "Scenes/S05_ProjectionDemo.h"
#include "Scenes/S06_MouseDemo.h"
#include "Scenes/S07_PickingDemo.h"

vector<Scene*> scenes;

void InitScene()
{
	scenes.push_back(new S07_PickingDemo());
}

void DestroyScene()
{
	for (Scene* scene : scenes)
		SafeDelete(scene);
}

void Update()
{
	for (Scene* scene : scenes)
		scene->Update();
}

void Render()
{
	for (Scene* scene : scenes)
		scene->Render();
}

void PostRender()
{
	RECT rect = { 0, 0, 800, 200 };
	wstring text = L"FPS : " + to_wstring(ImGui::GetIO().Framerate);
	DirectWrite::RenderText(text, rect);
}