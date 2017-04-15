#pragma once

#include "BoundingBox.h"
#include "QuadTree.h"
#include "NDimArray.h"
#include "Vorton.h"
#include "Vector2D.h"

#include <list>
#include <vector>

using namespace std;

class VortonSim
{
private:
	BoundingBox simulationRegion;
	list<Vorton*> vortons;
	QuadTree<Vorton>* vortonTree = nullptr;
	NDimArray<Vector2D> velocityGrid;
	NDimArray<vector<Vorton*>> vortonLocations;

	vector<int> gridDimensions;
	float xGridStep, yGridStep;

	bool isSetup = false;

	float gridPointThreshold = 0;
	float fluidViscosity = 1.0;

public:
	VortonSim();
	~VortonSim();

	void Initialise(const list<Vorton*>& vorts, const vector<int>& gridDim);
	void AddVorton(Vorton* vorton);

	void CalculateBoundingRegion();
	bool CalculateVelocityGrid();

	void Update(float delta);
};
