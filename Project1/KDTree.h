#pragma once

#include "Optional.h"

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template <int k, class X>
class Node
{
	vector<int> size;

	Node* parent;
	Node* children[k];

	list<Optional<X>*> objects;

	Node(const list<Optional<X>*> nodeObjects)
	{
		if (nodeObjects.size() > 1 && nodeObjects)
		{
			for (int child = 0; child < k; child++)
			{
				nodes.push_back(Node<k, X>());
			}
		}
	}
};

class BoundingRegion
{
public:
	vector<float> minima, maxima;
	
public:

	BoundingRegion(const vector<float>& min, const vector<float>& max) : minima(min), maxima(max) {}

	int Dimension() const { return minima.size(); }

	bool IsInsideRegion(const vector<float>& position) 
	{
		bool inBounds = true;
		for (int i=0;  i<minima.size(); i++)
		{
			inBounds = inBounds && (position[i] > minima[i]) && (position[i] < maxima[i]);
		}
		return inBounds;
	}

	BoundingRegion GetSubRegion(int region)
	{
		int noOfDivisions = pow(2, minima.size());
		vector<float> halfWidths;
		

	}
};

// Class X must have a member function GetPosition() which returns vector<float>, and have a constructor X(const list<X*>&).

template <class X>
class KDTree
{
private:

	const int noOfNodes = pow(2, k);

	KDTree* parent;	
	vector<KDTree<k,X>*> children;

	X* object;
	
	BoundingRegion boundingRegion;
	const int MIN_SIZE = 1;

	bool canBuild = false;
	bool treeBuilt = false;

	list<X*> pendingInsert;
	list<X*> pendingRemove;

public:
	KDTree(const BoundingRegion& boundingRegion, const list<X*>& objects)
	{
		Initialise(boundingRegion, objects)
	}
	~KDTree() {}

	void Initialise(const BoundingRegion& region, const list<X*>& objects)
	{
		if (region.size() == k)
		{
			boundingRegion = region;
			canBuild = true;
		}
		else
		{
			cout << "Error: Bounding region must correspond to KDTree dimension." << endl;
			canBuild = false;
		}

		children.resize(noOfNodes);

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

		X* object = new X(pendingInsert);

		for (int nodeNo = 0; nodeNo<noOfNodes; nodeNo++)
		{
			BoundingRegion nodeRegion = boundingRegion.GetSubRegion(nodeNo);
			list<X*> nodeObjects;
			remove_copy_if(pendingInsert.begin(), pendingInsert.end(), nodeObjects.begin(), [](X* obj) {return nodeRegion.IsInsideRegion(obj->GetPosition())};);

			children[nodeNo] = new KDTree<k, X>(nodeRegion, nodeObjects);
			childred[nodeNo]->BuildTree();
		}


		for (int dim = 0; dim < k; dim++)
		{
			for (int bisection = 0; bisection < 2; bisection++)
			{
				boundingRegion.minima[dim] +
				BoundingRegion nodeRegion(boundingRegion.minima);
				list<X*> nodeObjects;
				remove_copy_if(pendingInsert.begin(), pendingInsert.end(), nodeObjects.begin(), [](X* obj) {return nodeRegion.IsInsideRegion(obj->GetPosition())};);

				children[nodeNo] = new KDTree<k, X>(nodeRegion, nodeObjects);
				childred[nodeNo]->BuildTree();
			}
		}

		pendingInsert.clear();
		treeBuilt = true;
	}
};
