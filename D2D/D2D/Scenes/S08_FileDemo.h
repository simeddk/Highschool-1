#pragma once

#include "Scene.h"

class S08_FileDemo : public Scene
{
public:
	S08_FileDemo();
	~S08_FileDemo();

	void Update() override;
	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

private:
	void SaveAsCsv();
	void LoadAsCsv();

	void SaveMarkers();
	void LoadMarkers();

	void SaveXML();
	void LoadXML();

	void SaveBinary();
	void LoadBinary();

private:
	Shader* shader = nullptr;
	Sprite* background = nullptr;
	PerFrame* perFrame = nullptr;

	vector<class Marker*> markers;

	Shader* rectShader = nullptr;
	class Rect* rect = nullptr;

	Vector2 rectPosition;
	Color rectColor;

	class Marco* marco = nullptr;
	Sprite* scopeDog = nullptr;
};