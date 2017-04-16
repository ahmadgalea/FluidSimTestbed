#pragma once

#include "Optional.h"
#include "BoundingBox.h"
#include "Vector2D.h"

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Class X must have a member function GetPosition() which returns Vector2D, and have a constructor X(const list<X*>&).
template <class X>
class QuadTree
{
private:

	QuadTree<X>* parent = nullptr;
	QuadTree<X>* children[4] = { nullptr };

	X* object;

	BoundingBox boundingRegion;
	float minGridSize;

	bool treeBuilt = false;

	list<X*> pendingInsert;
	list<X*> pendingRemove;

public:

	QuadTree() {}
	QuadTree(const BoundingBox& boundingRegion, const list<X*>& objects, const float& minSize = 0.0f) : minGridSize(minSize)
	{
		Initialise(boundingRegion, objects);
	}
	~QuadTree() 
	{
		DestroyTree();
	}

	void Initialise(const BoundingBox& region, const list<X*>& objects)
	{
		boundingRegion = region;

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
		if (!treeBuilt)
		{
			BuildTree();
		}
	}

	// Should be parallelised
	void BuildTree()
	{
		object = new X(pendingInsert);

		float halfWidth = boundingRegion.width/2;
		float halfHeight = boundingRegion.height/2;

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

			if (nodeObjects.size() > 0 && quadrants[quad].width > minGridSize && quadrants[quad].height)
			{
				children[quad] = new QuadTree<X>(nodeRegion, quadrants[quad]);
				children[quad].parent = this;
				childred[quad]->BuildTree();
			}
			else
			{
				children[quad] = nullptr;
			}
		}
		pendingInsert.clear();
		treeBuilt = true;
	}

	void DestroyTree()
	{
		delete object;
		pendingInsert.clear();
		pendingRemove.clear();

		for (QuadTree<X>* child : children)
		{
			delete child;
		}
	}

	vector<X*> GetElementsExternalToPoint(const Vector2D& position, const float& threshold) const
	{
		vector<X*> externalElements;
		BoundingBox posBox(Vector2D(position.x - threshold, position.y - threshold), Vector2D(position.x + threshold, position.y + threshold));

		for (QuadTree<X>* child : children)
		{
			if (child != nullptr)
			{
				if (child->boundingRegion.IsOverlapping(posBox))
				{
					externalElements.push_back(child->object);
				}
				else
				{
					vector<X*> childElements = child->GetElementsExternalToPoint(position, threshold);
					externalElements.insert(externalElements.end(), childElements.begin(), childElements.end());
				}
			}
		}
		return externalElements;
	}
};
