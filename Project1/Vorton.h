#pragma once

#include "Vector2D.h"

#include <list>

using namespace std;

class Vorton
{
private:
	float vorticity;

	Vector2D position;
	bool foreground;

	float vortonRadius = 0.001;

public:
	Vorton() {}
	Vorton(const list<Vorton*>& vortons);
	~Vorton() {}

	float GetVorticity() const;

	Vector2D GetVelocityAtPosition(const Vector2D& referencePosition) const;

	Vector2D GetPosition() const;
	bool isForeground() const;
};