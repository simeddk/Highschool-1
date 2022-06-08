#pragma once

#include "Scene.h"

class S10_FileDialogDemo : public Scene
{
public:
	S10_FileDialogDemo();
	~S10_FileDialogDemo();

	void Update() override;
	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

private:
	void SaveBinary();
	void LoadBinary();

	void OnLoadCompleted(wstring file);
	void OnSaveCompleted(wstring file);

private:
	Shader* shader = nullptr;
	Sprite* background = nullptr;
	PerFrame* perFrame = nullptr;

	vector<class Marker*> markers;
};