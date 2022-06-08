#pragma once

#include "Scene.h"

class S05_ProjectionDemo : public Scene
{
public:
	S05_ProjectionDemo();
	~S05_ProjectionDemo();

	void Update() override;
	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

private:
	Shader* shader = nullptr;
	Sprite* background = nullptr;
	PerFrame* perFrame = nullptr;

};