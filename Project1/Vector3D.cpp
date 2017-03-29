#include "Vector3D.h"

#include "Vector2D.h"

Vector3D::Vector3D(const Vector2D& vec2)
{
	this->x = vec2.x;
	this->y = vec2.y;
	this->z = 0.0f;
}

Vector3D::Vector3D(const Vector2D& vec2, float zPos)
{
	this->x = vec2.x;
	this->y = vec2.y;
	this->z = zPos;
}
Vector3D& Vector3D::operator= (const Vector2D& vec2)
{
	this->x = vec2.x;
	this->y = vec2.y;
	this->z = 0.0f;
	return *this;
}

Vector3D Vector3D::operator * (const float& scalar) const
{
	return Vector3D(x * scalar, y * scalar, z * scalar);
}

void Vector3D::operator *= (const float& scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}

Vector3D Vector3D::operator / (const float& scalar) const
{
	return Vector3D(x / scalar, y / scalar, z / scalar);
}

void Vector3D::operator /= (const float& scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
}

Vector3D Vector3D::operator + (const Vector3D& otherVector) const
{
	return Vector3D(x + otherVector.x, y + otherVector.y, z + otherVector.z);
}

void Vector3D::operator += (const Vector3D& otherVector)
{
	this->x += otherVector.x;
	this->y += otherVector.y;
	this->z += otherVector.z;
}

Vector3D Vector3D::operator - (const Vector3D& otherVector) const
{
	return Vector3D(x - otherVector.x, y - otherVector.y, z - otherVector.z);
}

void Vector3D::operator -= (const Vector3D& otherVector)
{
	this->x -= otherVector.y;
	this->y -= otherVector.y;
	this->z -= otherVector.z;
}

Vector3D Vector3D::operator -() const
{
	return (*this) * -1.0;
}

bool Vector3D::operator == (const Vector3D& otherVector) const
{
	return ((x == otherVector.x) && (y == otherVector.y) && (z == otherVector.z));
}

bool Vector3D::operator != (const Vector3D& otherVector) const
{
	return ((x != otherVector.x) || (y != otherVector.y) || (z != otherVector.z));
}
float Vector3D::GetMagnitude() const
{
	return sqrt(x * x + y * y + z * z);
}
float Vector3D::GetMagnitudeSquared() const
{
	return x * x + y * y + z * z;
}

Vector3D Vector3D::GetNormalised() const
{
	return (*this) / GetMagnitude();
}

void Vector3D::Normalise()
{
	float magnitude = this->GetMagnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}


Vector2D Vector3D::XY() const
{
	return Vector2D(x, y);
}
Vector2D Vector3D::XZ() const
{
	return Vector2D(x, z);
}
Vector2D Vector3D::YZ() const
{
	return Vector2D(y, z);
}

float DotProduct(const Vector3D& vecA, const Vector3D& vecB)
{
	return vecA.x * vecB.x + vecA.y * vecB.y + vecA.z * vecB.z;
}

Vector3D CrossProduct(const Vector3D& vecA, const Vector3D& vecB)
{
	Vector3D crossVec;
	crossVec.x = vecA.y * vecB.z - vecA.z * vecB.y;
	crossVec.y = vecA.z * vecB.x - vecA.x * vecB.z;
	crossVec.z = vecA.x * vecB.y - vecA.y * vecB.x;
	return crossVec;
}

Vector3D GetPointBetween(const Vector3D& vec1, const Vector3D& vec2, const float& t)
{
	Vector3D betweenVec;
	betweenVec.x = vec2.x * t + vec1.x * (1.0f - t);
	betweenVec.y = vec2.y * t + vec1.y * (1.0f - t);
	betweenVec.z = vec2.z * t + vec1.z * (1.0f - t);
	return betweenVec;
}

std::ostream& operator<<(std::ostream& stream, const Vector3D& vec)
{
	stream << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
	return stream;
}