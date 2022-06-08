#pragma once

#include "stdafx.h"

class Test2
{
public:
	static void Start() { ImGui::Text("Game2 Start"); }
	void Render() { ImGui::Text("Game2 Render"); }
	string Div(float a, float b) { return to_string(a / b); }
};