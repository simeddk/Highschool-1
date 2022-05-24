#pragma once

#include "Scene.h"

class S01_Scene01Demo : public Scene
{
public:
	S01_Scene01Demo();
	~S01_Scene01Demo();

	void Update() override;
	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

private:
	Shader* shader = nullptr;
	PerFrame* perFrame = nullptr;

	class Background_Mario* background = nullptr;
	class Marco* marco = nullptr;
};