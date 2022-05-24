#pragma once

#include "Scene.h"

class S02_Scene02Demo : public Scene
{
public:
	S02_Scene02Demo();
	~S02_Scene02Demo();

	void Update() override;
	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

private:
	Shader* shader = nullptr;
	PerFrame* perFrame = nullptr;

	class Sprite* background = nullptr;
};