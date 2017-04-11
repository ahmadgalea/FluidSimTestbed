#pragma once

#include "Optional.h"
#include "Vector2D.h"

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


class BoundingBox
{
public:
	Vector2D minima, maxima;

public:

	BoundingBox(const Vector2D& min, const Vector2D& max) : minima(min), maxima(max) {}

	bool IsInsideRegion(const Vector2D& position)
	{
		return (position.x > minima.x) && (position.x < maxima.x) && (position.y > minima.y) && (position.y < maxima.y);

	}
};

// Class X must have a member function GetPosition() which returns Vector2D, and have a constructor X(const list<X*>&).

template <class X>
class QuadTree
{
private:

	QuadTree<X>* parent;
	QuadTree<X>* children[4];

	X* object;

	BoundingBox boundingRegion;
	const int MIN_SIZE = 1;

	bool canBuild = false;
	bool treeBuilt = false;

	list<X*> pendingInsert;
	list<X*> pendingRemove;

public:
	QuadTree(const BoundingBox& boundingRegion, const list<X*>& objects)
	{
		Initialise(boundingRegion, objects)
	}
	~QuadTree() {}

	void Initialise(const BoundingBox& region, const list<X*>& objects)
	{
		boundingRegion = region;
		canBuild = true;

		// perform tree construction in update phase, allows us to seperate initialisation from construction
		// so we can add objects in stages if need be without rebuilding.
		pendingInsert = objects;

	}

	void Insert(const X& object)
	{
		pendingInsertpush_back(&object);
	}

	void Remove(const X& object)
	{
		pendingRemove.push_back(&object);
	}

	void UpdateTree()
	{
		if (!treeBuilt && canBuild)
		{
			BuildTree();
		}
	}

	void BuildTree()
	{
		object = new X(pendingInsert);

		float halfWidth = (boundingRegion.maxima.x - boundingRegion.minima.x)/2;
		float halfHeight = (boundingRegion.maxima.y - boundingRegion.minima.y)/2;

		vector<BoundingBox> quadrants =
		{
			BoundingBox(Vector2D(boundingRegion.minima.x, boundingRegion.minima.y), Vector2D(boundingRegion.maxima.x - halfWidth, boundingRegion.maxima.y - halfHeight)),
			BoundingBox(Vector2D(boundingRegion.minima.x + halfWidth, boundingRegion.minima.y), Vector2D(boundingRegion.maxima.x, boundingRegion.maxima.y - halfHeight)),
			BoundingBox(Vector2D(boundingRegion.minima.x, boundingRegion.minima.y + halfHeight), Vector2D(boundingRegion.maxima.x - halfWidth, boundingRegion.maxima.y)),
			BoundingBox(Vector2D(boundingRegion.minima.x + halfWidth, boundingRegion.minima.y + halfHeight), Vector2D(boundingRegion.maxima.x, boundingRegion.maxima.y))
		};

		for (int quad = 0; quad < 4; quad++)
		{
			list<X*> nodeObjects;
			remove_copy_if(pendingInsert.begin(), pendingInsert.end(), nodeObjects.begin(), [quadrants&](X* obj) {return quadrants[quad].IsInsideRegion(obj->GetPosition())};);

			children[quad] = new QuadTree<X>(nodeRegion, quadrants[quad]);
			childred[quad]->BuildTree();
		}
		pendingInsert.clear();
		treeBuilt = true;
	}
};
