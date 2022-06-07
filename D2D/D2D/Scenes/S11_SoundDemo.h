#pragma once

#include "Scene.h"

class S11_SoundDemo : public Scene
{
public:
	S11_SoundDemo();
	~S11_SoundDemo();

	void Update() override;
	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

private:
	Shader* shader = nullptr;

	class Marco* marco = nullptr;
	Sprite* images[3];
	wstring names[3] = { L"BGM1", L"BGM2", L"BGM3" };
	int coverIndex = -1;
};