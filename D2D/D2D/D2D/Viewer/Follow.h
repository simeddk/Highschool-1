#pragma once

#include "IFollow.h"

class Follow : public Camera
{
public:
	Follow(IFollow* focusObject = nullptr);
	~Follow();

	void Update() override;

	void ChangeFocus(IFollow* newFocusObject);

private:
	IFollow* focusObject;
};