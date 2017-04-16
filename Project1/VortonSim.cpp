
#include "VortonSim.h"

#include <algorithm>
#include <iostream>

VortonSim::VortonSim()
{
}

VortonSim::~VortonSim()
{
	if (vortonTree != nullptr)
	{
		delete vortonTree;
	}
}

void VortonSim::Initialise(const list<Vorton*>& vorts, const vector<int>& gridDim)
{
	if (gridDim.size() == 2 && vorts.size() > 0)
	{
		vortons = vorts;
		gridDimensions = gridDim;
		velocityGrid.Initialise(gridDim);
		vortonLocations.Initialise(gridDim);
		isSetup = true;
	}
	else
	{
		cout << "Error: Vorton simulation grid must be 2D!" << endl;
		isSetup = false;
	}
}

void VortonSim::AddVorton(Vorton* vorton)
{
	vortons.push_back(vorton);
}

void VortonSim::CalculateBoundingRegion()
{
	auto xMinMax = minmax(vortons.begin(), vortons.end(), [](auto v1, auto v2) {return (*v1)->GetPosition().x < (*v2)->GetPosition().x; });
	auto yMinMax = minmax(vortons.begin(), vortons.end(), [](auto v1, auto v2) {return (*v1)->GetPosition().y < (*v2)->GetPosition().y; });

	simulationRegion = BoundingBox(Vector2D((*xMinMax.first)->GetPosition().x, (*yMinMax.first)->GetPosition().y), Vector2D((*xMinMax.second)->GetPosition().x, (*yMinMax.second)->GetPosition().y));

	xGridStep = simulationRegion.width / ((float)gridDimensions.at(0));
	yGridStep = simulationRegion.height / ((float)gridDimensions.at(1));
}

bool VortonSim::CalculateVelocityGrid()
{
	// Should be parallelised.
	for (int j = 0; j < gridDimensions.at(1); j++)
	{
		for (int i = 0; i < gridDimensions.at(0); i++)
		{
			// Initialise grid position.
			Optional<Vector2D> gridPoint = velocityGrid.GetOptional({ i, j });
			Optional<vector<Vorton*>> vortonRefGridPoint = vortonLocations.GetOptional({ i, j });

			if (gridPoint.IsValid() && vortonRefGridPoint.IsValid())
			{
				velocityGrid.Set({ i, j }, Vector2D(0.0f, 0.0f));
				vector<Vorton*> emptyArray;
				vortonLocations.Set({ i, j }, emptyArray);
			}
			else
			{
				cout << "Error: Vorton velocity grid not properly initialised!" << endl;
				return false;
			}

			// Calculate grid position;
			float xPos = ((float)i)*xGridStep + simulationRegion.minima.x;
			float yPos = ((float)j)*yGridStep + simulationRegion.minima.y;
			Vector2D position(xPos, yPos);

			// Get contributing vortons(and super vortons).
			vector<Vorton*> contributingVortons = vortonTree->GetElementsExternalToPoint(position, gridPointThreshold);

			// Calculate velocity at grid position.
			for (Vorton* vorton : contributingVortons)
			{
				velocityGrid.Set({ i, j }, gridPoint.GetValue() + vorton->GetVelocityAtPosition(position));

				// Add fundamental vortons to vortonLocation array. Used in diffusion calc.
				if (vorton->isFundamental)
				{
					vector<Vorton*> elementVorticities = vortonLocations.GetOptional({ i, j }).GetValue();
					elementVorticities.push_back(vorton);
					vortonLocations.Set({ i, j }, elementVorticities);
				}
			}

			// Calculate velocity jacobian.
			// this is for vorton tilting ans stretching, which is zero in 2D.
		}
	}

	return true;
}
void VortonSim::UpdateWithGrid(float delta)
{
	if (isSetup)
	{
		// Create box around Vortons
		CalculateBoundingRegion();

		// Create vorton quadtree (should be parallelised).
		vortonTree = new QuadTree<Vorton>(simulationRegion, vortons);

		// Calculate velocity grid from vortons (including Jacobian calculation?).
		if (!CalculateVelocityGrid())
		{
			return;
		}

		// Interpolate velocity back to vortons and calculate tilting and stretching.
		// This term is zero in 2D.

		// Calculate diffusion of vortons.


		// Advect vortons.

		delete vortonTree;
	}
}

void VortonSim::CalculateVelocityAndDiffusionAtVortons()
{
	for (Vorton* vorton : vortons)
	{
		// Get contributing vortons(and super vortons).
		vector<Vorton*> contributingVortons = vortonTree->GetElementsExternalToPoint(vorton->GetPosition(), gridPointThreshold);

		Vector2D velocity(0.0f, 0.0f);
		float diffusionRate = 0.0f;

		// Calculate velocity at grid position.
		for (Vorton* interactingVorton : contributingVortons)
		{
			velocity += interactingVorton->GetVelocityAtPosition(vorton->GetPosition());

			// Is vorton a nearest neighbour?
			if (interactingVorton->isFundamental)
			{
				// Is interactingVorton in front of Vorton?
				Vector2D distance = interactingVorton->GetPosition() - vorton->GetPosition();
				if ((vorton->GetVelocity().x*distance.x + vorton->GetVelocity().y*distance.y) > 0.0f)
				{
					diffusionRate += fluidViscosity*(interactingVorton->GetVorticity() - vorton->GetVorticity());
				}
			}
		}
		vorton->SetVelocity(velocity);
		vorton->SetVorticityROC(diffusionRate);
	}
}

void VortonSim::UpdateVortons(float delta)
{
	for (Vorton* vorton : vortons)
	{
		vorton->SetVorticity(vorton->GetVorticity() + vorton->GetVorticityROC()*delta);

		vorton->SetPosition(vorton->GetPosition() + vorton->GetVelocity()*delta);
	}
}

void VortonSim::Update(float delta)
{
	// Create box around Vortons
	CalculateBoundingRegion();

	// Create vorton quadtree (should be parallelised).
	vortonTree = new QuadTree<Vorton>(simulationRegion, vortons);

	CalculateVelocityAndDiffusionAtVortons();

	UpdateVortons(delta);
}