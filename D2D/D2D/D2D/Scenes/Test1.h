#pragma once

#include "stdafx.h"

class Test1
{
public:
	static void Start() { ImGui::Text("Game1 Start"); }
	void Render() { ImGui::Text("Game1 Render"); }
	string Mul(float a, float b) { return to_string(a * b); }
};