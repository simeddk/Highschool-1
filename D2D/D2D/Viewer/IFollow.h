#pragma once

#include "stdafx.h"

class IFollow
{
public:
	virtual void Focus(Vector2* focusPosition) = 0;
};