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

	ImGui::SameLine();
	if (ImGui::Button("Load Bin"))
		LoadBinary();

	ImGui::Spacing();
	ImGui::Separator();
	if (ImGui::Button("Open(Exmple)"))
	{
		function<void(wstring)> loadDelegate = bind(&S10_FileDialogDemo::OnLoadCompleted, this, placeholders::_1);
		Path::OpenFileDialog(L"ScopeDog.png", L"Data\0*.txt;*.csv;*.bin\0XML\0*.xml\0", L"../../_Datas/", loadDelegate, Hwnd);
	}

	if (ImGui::Button("Save"))
	{
		function<void(wstring)> saveDelegate = bind(&S10_FileDialogDemo::OnSaveCompleted, this, placeholders::_1);
		Path::SaveFileDialog(L"", L"Binary\0*.bin\0", L"../../_Datas", saveDelegate, Hwnd);
	}

	if (ImGui::Button("Load"))
	{
		function<void(wstring)> loadDelegate = bind(&S10_FileDialogDemo::OnLoadCompleted, this, placeholders::_1);
		Path::SaveFileDialog(L"", L"Binary\0*.bin\0", L"../../_Datas", loadDelegate, Hwnd);
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

void S10_FileDialogDemo::OnLoadCompleted(wstring file)
{
	markers.clear();

	BinaryReader* r = new BinaryReader(file);

	UINT count;
	count = r->UInt();

	for (size_t i = 0; i < count; i++)
	{
		UINT index = r->UInt();
		Vector2 position = r->Vector2();

		markers.push_back(new Marker(shader, position));
	}

	SafeDelete(r);
}

void S10_FileDialogDemo::OnSaveCompleted(wstring file)
{
	BinaryWriter* w = new BinaryWriter(file + L".bin");

	w->UInt(markers.size());

	for (size_t i = 0; i < markers.size(); i++)
	{
		w->UInt(i);
		w->Vector2(markers[i]->Position());
	}

	SafeDelete(w);

	wstring msg = file + L"\n저장을 완료했단다.";
	MessageBox(Hwnd, msg.c_str(), L"저장 완료", MB_OK);
}
