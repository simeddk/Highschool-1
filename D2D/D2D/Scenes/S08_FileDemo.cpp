#include "stdafx.h"
#include "S08_FileDemo.h"
#include "Objects/Marker.h"
#include "Objects/Rect.h"
#include "Objects/Marco.h"
#include "Utilities/Xml.h"

S08_FileDemo::S08_FileDemo()
{
	shader = new Shader(L"04_Sprite.fx");
	background = new Sprite(shader, L"Background/SonicStage.png");
	perFrame = new PerFrame(shader);

	rectShader = new Shader(L"05_Bounding.fx");
	rect = new Rect(rectShader, Vector2(100, 100), Vector2(100, 100));

	rectPosition = rect->Position();
	rectColor = rect->Color();

	marco = new Marco(shader, Vector2(0, 0), Vector2(1, 1));
}

S08_FileDemo::~S08_FileDemo()
{
	SafeDelete(shader);
	SafeDelete(background);
	SafeDelete(perFrame);

	SafeDelete(rectShader);
	SafeDelete(rect);

	for (Marker* marker : markers)
		SafeDelete(marker);

	SafeDelete(marco);
}

void S08_FileDemo::Update()
{
	if (ImGui::CollapsingHeader("Rect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::SliderFloat2("Position", rectPosition, -1000.0f, +1000.0f);
		ImGui::ColorEdit3("Color", rectColor);

		rect->Position(rectPosition);
		rect->Color(rectColor);

		if (ImGui::Button("Save As CSV"))
			SaveAsCsv();

		ImGui::SameLine();
		if (ImGui::Button("Load As CSV"))
			LoadAsCsv();
	}

	if (Mouse->Down(LButton))
	{
		Vector2 mouse = Mouse->Position_World();
		markers.push_back(new Marker(shader, mouse));
	}

	ImGui::Separator();
	ImGui::Spacing();
	if (ImGui::CollapsingHeader("Markers"), ImGuiTreeNodeFlags_DefaultOpen)
	{
		if (ImGui::Button("Save Markers"))
			SaveMarkers();
		
		ImGui::SameLine();
		if (ImGui::Button("Load Markers"))
			LoadMarkers();

		if (ImGui::Button("Clear Markers"))
			markers.clear();
	}

	ImGui::Separator();
	ImGui::Spacing();
	if (ImGui::CollapsingHeader("XML"), ImGuiTreeNodeFlags_DefaultOpen)
	{
		//Save Xml
		if (ImGui::ImageButton
		(
			marco->GetSprite()->SRV(),
			ImVec2(marco->GetSprite()->TextureSize().x, marco->GetSprite()->TextureSize().y),
			ImVec2(marco->GetSprite()->StartUV().x, marco->GetSprite()->StartUV().y),
			ImVec2(marco->GetSprite()->EndUV().x, marco->GetSprite()->EndUV().y),
			5,
			ImVec4(0, 0, 0, 1),
			ImVec4(1, 0, 0, 1)
		))
		{
			SaveXML();
		}

		//Load Xml
		ImGui::SameLine();
		if (ImGui::ImageButton
		(
			marco->GetSprite()->SRV(),
			ImVec2(marco->GetSprite()->TextureSize().x, marco->GetSprite()->TextureSize().y),
			ImVec2(marco->GetSprite()->StartUV().x, marco->GetSprite()->StartUV().y),
			ImVec2(marco->GetSprite()->EndUV().x, marco->GetSprite()->EndUV().y),
			5,
			ImVec4(0, 0, 0, 1),
			ImVec4(0, 1, 0, 1)
		))
		{
			LoadXML();
		}
	}


	perFrame->Update();
	background->Update();
	marco->Update();
	rect->Update();

	for (Marker* marker : markers)
		marker->Update();

}

void S08_FileDemo::Render()
{
	perFrame->Render();
	background->Render();
	rect->Render();

	for (Marker* marker : markers)
		marker->Render();

	
	
}

void S08_FileDemo::SaveAsCsv()
{
	Path::CreateFolders("../../_Datas/");

	FILE* file = nullptr;
	fopen_s(&file, "../../_Datas/Rect.csv", "w");
	fprintf
	(
		file,
		"%.2f,%.2f,%.2f,%.2f,%.2f",
		rect->Position().x, rect->Position().y,
		rect->Color().r, rect->Color().g, rect->Color().b
	);
	fclose(file);
}

void S08_FileDemo::LoadAsCsv()
{
	FILE* file = nullptr;
	fopen_s(&file, "../../_Datas/Rect.csv", "r");
	fscanf_s
	(
		file,
		"%f,%f,%f,%f,%f",
		&rectPosition.x, &rectPosition.y,
		&rectColor.r, &rectColor.g, &rectColor.b
	);
	fclose(file);

	rect->Position(rectPosition);
	rect->Color(rectColor);
}

void S08_FileDemo::SaveMarkers()
{
	FILE* file = nullptr;
	fopen_s(&file, "../../_Datas/Marekrs.txt", "w");

	fprintf(file ,"%d\n", markers.size());

	for (int i = 0; i < markers.size(); i++)
		fprintf(file, "%d,%.2f,%.2f\n", i, markers[i]->Position().x, markers[i]->Position().y);

	fclose(file);
}

void S08_FileDemo::LoadMarkers()
{
	if (Path::ExistFile("../../_Datas/Marekrs.txt"))
	{
		markers.clear();

		FILE* file = nullptr;
		fopen_s(&file, "../../_Datas/Marekrs.txt", "r");

		UINT count;
		fscanf_s(file, "%d", &count);

		for (int i = 0; i < count; i++)
		{
			UINT index;
			Vector2 position;
			fscanf_s(file, "%d, %f, %f", &index, &position.x, &position.y);

			markers.push_back(new Marker(shader, position));
		}

		fclose(file);

	}
}

void S08_FileDemo::SaveXML()
{
	Xml::XMLDocument* document = new Xml::XMLDocument();
	Xml::XMLDeclaration* decl = document->NewDeclaration();
	document->LinkEndChild(decl);

	Xml::XMLElement* root = document->NewElement("Background");
	root->SetAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	root->SetAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
	document->LinkEndChild(root);

	Xml::XMLElement* node = document->NewElement("Sprite");
	root->LinkEndChild(node);

	Xml::XMLElement* element = nullptr;

	element = document->NewElement("Name");
	element->SetText(String::ToString(background->GetTextureFile()).c_str());
	node->LinkEndChild(element);

	element = document->NewElement("Width");
	element->SetText(background->ScaledTextureSize().x);
	node->LinkEndChild(element);

	element = document->NewElement("Height");
	element->SetText(background->ScaledTextureSize().y);
	node->LinkEndChild(element);

	document->SaveFile("../../_Datas/Background.xml");

}

void S08_FileDemo::LoadXML()
{
}
