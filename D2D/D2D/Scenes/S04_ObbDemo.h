#pragma once

#include "Scene.h"

class S04_ObbDemo : public Scene
{
public:
	S04_ObbDemo();
	~S04_ObbDemo();

	void Update() override;
	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

private:
	Shader* shader = nullptr;
	
	class Marco* marco = nullptr;
	class Fire* fire = nullptr;
};