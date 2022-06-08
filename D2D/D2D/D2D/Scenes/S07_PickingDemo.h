#pragma once

#include "Scene.h"

class S07_PickingDemo : public Scene
{
public:
	S07_PickingDemo();
	~S07_PickingDemo();

	void Update() override;
	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

private:
	Shader* shader = nullptr;
	Sprite* background = nullptr;
	PerFrame* perFrame = nullptr;

	vector<class Marker*> markers;

	Shader* rectShader = nullptr;
	class Rect* rect = nullptr;
};