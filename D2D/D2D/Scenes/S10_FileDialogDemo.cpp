#include "stdafx.h"
#include "S10_FileDialogDemo.h"
#include "Objects/Marker.h"


S10_FileDialogDemo::S10_FileDialogDemo()
{
	shader = new Shader(L"04_Sprite.fx");
	background = new Sprite(shader, L"Background/SonicStage.png");
	perFrame = new PerFrame(shader);
}

S10_FileDialogDemo::~S10_FileDialogDemo()
{
	SafeDelete(shader);
	SafeDelete(background);
	SafeDelete(perFrame);

	for (Marker* marker : markers)
		SafeDelete(marker);
}

void S10_FileDialogDemo::Update()
{
	if (Mouse->Press(LButton))
	{
		Vector2 mouse = Mouse->Position_World();
		markers.push_back(new Marker(shader, mouse));
	}

	if (ImGui::Button("Save Bin"))
		SaveBinary();

	if (ImGui::Button("Load Bin"))
		LoadBinary();

	ImGui::Spacing();
	ImGui::Separator();
	if (ImGui::Button("Open(Exmple)"))
	{
		Path::OpenFileDialog(L"ScopeDog.png", Path::ImageFilter, L"../../_Textures/", nullptr, Hwnd);
	}

	perFrame->Update();
	background->Update();

	for (Marker* marker : markers)
		marker->Update();

}

void S10_FileDialogDemo::Render()
{
	perFrame->Render();
	background->Render();

	for (Marker* marker : markers)
		marker->Render();
}

void S10_FileDialogDemo::SaveBinary()
{
	BinaryWriter* w = new BinaryWriter(L"../../_Datas/Markers.bin");

	w->UInt(markers.size());

	for (size_t i = 0; i < markers.size(); i++)
	{
		w->UInt(i);
		w->Vector2(markers[i]->Position());
	}

	SafeDelete(w);

}

void S10_FileDialogDemo::LoadBinary()
{
	if (Path::ExistFile(L"../../_Datas/Markers.bin") == false) return;
	
	Performance p;
	p.Start();

	markers.clear();

	BinaryReader* r = new BinaryReader(L"../../_Datas/Markers.bin");

	UINT count;
	count = r->UInt();

	for (size_t i = 0; i < count; i++)
	{
		UINT index = r->UInt();
		Vector2 position = r->Vector2();

		markers.push_back(new Marker(shader, position));
	}

	float elapsed = p.End();
	MessageBox(Hwnd, to_wstring(elapsed).c_str(), L"Eplased Bin", MB_OK);

	SafeDelete(r);
}
