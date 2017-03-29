/*code by Finn Morgan, 2015 */
#include "Vector2D.h"


using namespace std;

Vector2D Vector2D::operator * (const float& scalar) const
{
	return Vector2D(x * scalar, y * scalar);
}

void Vector2D::operator *= (const float& scalar)
{
	x *= scalar;
	y *= scalar;
}

Vector2D Vector2D::operator / (const float& scalar) const
{
	return Vector2D(x / scalar, y / scalar);
}

void Vector2D::operator /= (const float& scalar)
{
	x /= scalar;
	y /= scalar;
}

Vector2D Vector2D::operator + (const Vector2D& otherVector) const
{
	return Vector2D(x + otherVector.x, y + otherVector.y);
}

void Vector2D::operator += (const Vector2D& otherVector)
{
	this->x += otherVector.x;
	this->y += otherVector.y;
}

Vector2D Vector2D::operator - (const Vector2D& otherVector) const
{
	return Vector2D(x - otherVector.x, y - otherVector.y);
}

void Vector2D::operator -= (const Vector2D& otherVector)
{
	this->x -= otherVector.x;
	this->y -= otherVector.y;
}

Vector2D Vector2D::operator -() const
{
	return (*this) * -1.0;
}

bool Vector2D::operator == (const Vector2D& otherVector) const
{
	return ((x == otherVector.x) && (y == otherVector.y));
}

bool Vector2D::operator != (const Vector2D& otherVector) const
{
	return ((x != otherVector.x) || (y != otherVector.y));
}


float Vector2D::GetMagnitude() const
{
	return sqrt(x * x + y * y);
}
float Vector2D::GetMagnitudeSquared() const
{
	return x * x + y * y;
}

Vector2D Vector2D::GetNormalised() const
{
	return (*this) / GetMagnitude();
}

void Vector2D::Normalise()
{
	float magnitude = this->GetMagnitude();
	x /= magnitude;
	y /= magnitude;
}

//Rotates the vector by a certain amount of radians, anticlockwise.
void Vector2D::RotatePoint(const float& angle)
{
	float cosAngle = cos(-angle);
	float sinAngle = sin(-angle);
	float tempX = x * cosAngle + y * sinAngle;
	y = -x * sinAngle + y * cosAngle;
	x = tempX;

}


void Vector2D::RotatePointBy90()
{
	float temp = y;
	y = x;
	x = -temp;
}
void Vector2D::RotatePointBy180()
{
	y *= -1;
	x *= -1;
}
void Vector2D::RotatePointBy270()
{
	float temp = x;
	x = y;
	y = -temp;
}


//Returns a float, representing the vector's angle in radians (in unit circle terms).
float Vector2D::GetBearing() const
{
	return atan2(y, x);
}


Vector2D Vector2D::GetReflectedAbout(const Vector2D& otherVec)
{
	Vector2D projectedComponent = GetParallelComponent(*this, otherVec);
	Vector2D otherComponent = GetPerpendicularComponent(*this, otherVec);
	otherComponent *= -1.0f;
	return projectedComponent + otherComponent;
}

Vector2D GetPointBetween(const Vector2D& point1, const Vector2D& point2, const float& t)
{
	float midX, midY;

	midX = ((point2.x - point1.x) * t) + point1.x;
	midY = ((point2.y - point1.y) * t) + point1.y;

	return Vector2D(midX, midY);
}

Vector2D GetParallelComponent(const Vector2D& projector, const Vector2D& projectee)
{
	return (projectee * DotProduct(projector, projectee)) / projectee.GetMagnitudeSquared();
}
Vector2D GetPerpendicularComponent(const Vector2D& projector, const Vector2D& projectee)
{
	return projector - GetParallelComponent(projector, projectee);
}

float DotProduct(const Vector2D& vecA, const Vector2D& vecB)
{
	return vecA.x * vecB.x + vecA.y * vecB.y;
}

ostream& operator<<(ostream& stream, const Vector2D& vec)
{
	stream << '(' << vec.x << ',' << vec.y << ')';
	return stream;
}



float GetAngleBetween(const Vector2D& vecA, const Vector2D& vecB)
{
	return acos(DotProduct(vecA.GetNormalised(), vecB.GetNormalised()));
}
float GetAnticlockwiseTurn(Vector2D preturnVec, Vector2D postturnVec)
{
	preturnVec.Normalise();
	postturnVec.Normalise();
	float lesserAngle = acos(DotProduct(preturnVec, postturnVec));



	//Fake 2D cross product thingy
	float zCross = preturnVec.x * postturnVec.y - preturnVec.y * postturnVec.x;

	if (isnan(lesserAngle))
	{
		//cout << "Shitfuckballs";
		return (float)-M_PI_2;
	}

	if (zCross > 0)
	{
		return lesserAngle;
	}
	else
	{
		return 2.0f * (float)M_PI - lesserAngle;
	}
}