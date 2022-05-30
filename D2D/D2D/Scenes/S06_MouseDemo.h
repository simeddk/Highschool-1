#pragma once

#include "Scene.h"

class S06_MouseDemo : public Scene
{
public:
	S06_MouseDemo();
	~S06_MouseDemo();

	void Update() override;
	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

private:
	Shader* shader = nullptr;
	Sprite* background = nullptr;
	PerFrame* perFrame = nullptr;

};