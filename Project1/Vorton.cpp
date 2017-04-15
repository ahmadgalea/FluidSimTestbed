#include "Vorton.h"

#include <numeric>
#include <math.h>

Vorton::Vorton(const list<Vorton*>& vortons)
{
	for (Vorton* vorton : vortons)
	{
		vorticity += vorton->GetVorticity();

		position += vorton->GetPosition()*fabs(vorton->GetVorticity());

		weight++;
	}
}

float Vorton::GetVorticity() const
{
	return vorticity;
}

Vector2D Vorton::GetVelocityAtPosition(const Vector2D& referencePosition) const
{
	Vector2D r (referencePosition.x - position.x, referencePosition.y - position.y);
	float rMag = r.GetMagnitude();
	float rad;
	rMag < vortonRadius ? rad = vortonRadius : rad = rMag;

	// Returns Vector3D(vorticity) x Vector3D(r) / r^3, where Vector3D(r) =  Vector3D(referencePosition) - Vector3D(position).
	// Use 3D vectors because vorticity is defined in z-direction.
	return Vector2D(vorticity*(-r.y), vorticity*(r.x))/(rad*rad*rad); 
}

Vector2D Vorton::GetPosition() const
{
	return position;
}

bool Vorton::isForeground() const
{
	return foreground;
}