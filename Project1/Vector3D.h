#pragma once

class Vector2D;

#include <iostream>

class Vector3D
{
public:
	float x;
	float y;
	float z;

	Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3D(float x1, float y1, float z1) : x(x1), y(y1), z(z1) {}

	Vector3D(const Vector2D& vec2);
	Vector3D(const Vector2D& vec2, float zPos);
	Vector3D& operator= (const Vector2D& vec2);

	Vector3D operator * (const float& scalar) const;
	void operator *= (const float& scalar);

	Vector3D operator / (const float& scalar) const;
	void operator /= (const float& scalar);

	Vector3D operator + (const Vector3D& otherVector) const;
	void operator += (const Vector3D& otherVector);

	Vector3D operator - (const Vector3D& otherVector) const;
	void operator -= (const Vector3D& otherVector);

	Vector3D operator -() const;

	//These currently just do a (somewhat sketchy) component-wise equality check - no error tolerance is involved.
	bool operator == (const Vector3D& otherVector) const;
	bool operator != (const Vector3D& otherVector) const;


	float GetMagnitude() const;
	float GetMagnitudeSquared() const;
	Vector3D GetNormalised() const;
	void Normalise();

	Vector2D XY() const;
	Vector2D XZ() const;
	Vector2D YZ() const;
};

float DotProduct(const Vector3D &vecA, const Vector3D &vecB);
Vector3D CrossProduct(const Vector3D &vecA, const Vector3D &vecB);

Vector3D GetPointBetween(const Vector3D& vec1, const Vector3D& vec2, const float& t = 0.5f);

std::ostream& operator<<(std::ostream& stream, const Vector3D& vec);