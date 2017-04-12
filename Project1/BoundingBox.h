#pragma once
#include "Optional.h"
#include "Vector2D.h"

class BoundingBox
{
public:
	Vector2D minima, maxima;
	float width, height;
	Vector2D origin;

public:

	BoundingBox() : minima(Vector2D(0.0f, 0.0f)), maxima(Vector2D(0.0f, 0.0f)), width(0.0f), height(0.0f), origin(Vector2D(0.0f, 0.0f)) {}

	BoundingBox(const Vector2D& min, const Vector2D& max) : minima(min), maxima(max) 
	{ 
		width = maxima.x - minima.x;
		height = maxima.y - minima.y;
		origin = Vector2D(minima.x + width/2, minima.y + height/2);
	}

	bool IsInsideRegion(const Vector2D& position)
	{
		return (position.x > minima.x) && (position.x < maxima.x) && (position.y > minima.y) && (position.y < maxima.y);

	}

	bool IsOverlapping(const BoundingBox& box)
	{
		bool xOverlapping = (box.origin.x < origin.x && box.maxima.x > minima.x) || (box.origin.x > origin.x && maxima.x > box.minima.x);
		bool yOverlapping = (box.origin.y < origin.y && box.maxima.y > minima.y) || (box.origin.y > origin.y && maxima.y > box.minima.y);
		return xOverlapping && yOverlapping;
	}
};