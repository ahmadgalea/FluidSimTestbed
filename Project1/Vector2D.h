/*code by Finn Morgan, 2015 */

#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

class Vector2D {
public:

	float x;
	float y;

	Vector2D() : x(0.0), y(0.0) {}
	Vector2D(float x1, float y1) : x(x1), y(y1) {}

	Vector2D operator * (const float& scalar) const;
	void operator *= (const float& scalar);

	Vector2D operator / (const float& scalar) const;
	void operator /= (const float& scalar);

	Vector2D operator + (const Vector2D& otherVector) const;
	void operator += (const Vector2D& otherVector);

	Vector2D operator - (const Vector2D& otherVector) const;
	void operator -= (const Vector2D& otherVector);

	Vector2D operator -() const;

	//These currently just do a (somewhat sketchy) component-wise equality check - no error tolerance is involved.
	bool operator == (const Vector2D& otherVector) const;
	bool operator != (const Vector2D& otherVector) const;

	float GetMagnitude() const;
	float GetMagnitudeSquared() const;
	Vector2D GetNormalised() const;
	void Normalise();
	void RotatePoint(const float &angle);

	void RotatePointBy90();
	void RotatePointBy180();
	void RotatePointBy270();

	float GetBearing() const;

	Vector2D GetReflectedAbout(const Vector2D& otherVec);

};

Vector2D GetPointBetween(const Vector2D& point1, const Vector2D& point2, const float& t = 0.5);

Vector2D GetParallelComponent(const Vector2D &projector, const Vector2D &projectee);
Vector2D GetPerpendicularComponent(const Vector2D &projector, const Vector2D &projectee);


float DotProduct(const Vector2D &vecA, const Vector2D &vecB);

float GetAngleBetween(const Vector2D& vecA, const Vector2D& vecB);
float GetAnticlockwiseTurn(Vector2D preturnVec, Vector2D postturnVec);

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec);
#pragma once
