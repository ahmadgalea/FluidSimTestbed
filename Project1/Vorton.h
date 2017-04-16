#pragma once

#include "Vector2D.h"

#include <list>

using namespace std;

class Vorton
{
private:
	float vorticity;

	Vector2D position;
	Vector2D velocity;
	bool foreground;

	float vortonROC;

	float vortonRadius = 0.001;
public:
	//unsigned int weight = 1; // might be used for optimisation 
	bool isFundamental = true;
public:
	Vorton() {}
	Vorton(const list<Vorton*>& vortons);
	~Vorton() {}

	float GetVorticity() const;
	void SetVorticity(const float& vort);

	Vector2D GetVelocityAtPosition(const Vector2D& referencePosition) const;

	Vector2D GetPosition() const;
	void SetPosition(const Vector2D& pos);

	Vector2D GetVelocity() const;
	void SetVelocity(const Vector2D& vel);

	bool isForeground() const;

	float GetVorticityROC() const;
	void SetVorticityROC(const float& ROC);
};