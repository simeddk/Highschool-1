#include "stdafx.h"
#include "Systems/Device.h"

#include "Scenes/Scene.h"
#include "Scenes/S01_Scene01Demo.h"
#include "Scenes/S02_Scene02Demo.h"

vector<Scene*> scenes;
UINT sceneIndex = 0;

void InitScene()
{
	scenes.push_back(new S01_Scene01Demo());
	scenes.push_back(new S02_Scene02Demo());
}

void DestroyScene()
{
	for (Scene* scene : scenes)
		SafeDelete(scene);
}

void Update()
{
	const char* sceneList[] = { "Mario Stage", "Final Fight Stage" };

	ImGui::Combo("Select Scene", (int*)&sceneIndex, sceneList, 2);
	ImGui::Text("%d", sceneIndex);
	
	scenes[sceneIndex]->Update();

	/*for (Scene* scene : scenes)
		scene->Update();*/
}

void Render()
{
	scenes[sceneIndex]->Render();

	/*for (Scene* scene : scenes)
		scene->Render();*/
}

void PostRender()
{
	RECT rect = { 0, 0, 800, 200 };
	wstring text = L"FPS : " + to_wstring(ImGui::GetIO().Framerate);
	DirectWrite::RenderText(text, rect);
}