#pragma once

#include "Vector2D.h"

class Vorton
{
public:
	Vector2D vorticity;
	Vector2D position;
	bool foreground;

public:
	Vorton() {}
	~Vorton() {}
};