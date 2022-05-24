#pragma once

#include "Scene.h"

class S03_AabbDemo : public Scene
{
public:
	S03_AabbDemo();
	~S03_AabbDemo();

	void Update() override;
	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

private:
	Shader* shader = nullptr;
	
	class Marco* marco = nullptr;
	class Marker* marker = nullptr;
	class Fire* fire = nullptr;
};