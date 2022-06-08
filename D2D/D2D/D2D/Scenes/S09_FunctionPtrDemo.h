#pragma once

#include "Scene.h"

class S09_FunctionPtrDemo : public Scene
{
public:
	S09_FunctionPtrDemo();
	~S09_FunctionPtrDemo();

	void Update() override;
	void PreRender() override {};
	void Render() override;
	void PostRender() override {};

private:
	
};