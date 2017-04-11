#pragma once

#include "Optional.h"
#include "StackArray.h"

#include <cstdarg>
#include <vector>
#include <assert.h>
#include <iostream>
#include <functional>


using namespace std;

//Different behaviours for if you try to access something outside the array bounds.
//NB Doesn't do anything yet.
enum class ArrayMode
{
	Clamp,
	Wrap,
	Assert,
	Throw
};

template <class X>
class NDimArray
{
private:
	Optional<X>* values = nullptr;
	int order = -1;
	int elementCount = -1;
	vector<int> dimensions;
	vector<int> dimMult;	//We precalculate these values so we don't have nested iteration for each lookup (ouch).

public:

	NDimArray() {}
	NDimArray(const vector<int> &dimensionsInit)
	{
		Initialise(dimensionsInit);
	}

	void operator= (const NDimArray &other)
	{
		if (other.values != nullptr)
		{
			if (this->values != nullptr)
			{
				delete[] values;
				dimensions.clear();
				dimMult.clear();
			}
			order = other.order;
			for (int i = 0; i < order; i++)
			{
				dimensions.push_back(other.dimensions[i]);
				dimMult.push_back(other.dimMult[i]);
			}
			elementCount = other.elementCount;
			values = new Optional<X>[elementCount];
			for (int i = 0; i < elementCount; i++)
			{
				values[i] = other.values[i];
			}
			//memcpy(values, other.values, sizeof(Optional<X>) * elementCount);
		}
		else
		{
			values = nullptr;
		}
	}
	NDimArray(const NDimArray &other)
	{
		if (other.values != nullptr)
		{
			if (this->values != nullptr)
			{
				delete[] values;
				dimensions.clear();
				dimMult.clear();
			}
			order = other.order;
			for (int i = 0; i < order; i++)
			{
				dimensions.push_back(other.dimensions[i]);
				dimMult.push_back(other.dimMult[i]);
			}
			elementCount = other.elementCount;
			values = new Optional<X>[elementCount];
			for (int i = 0; i < elementCount; i++)
			{
				values[i] = other.values[i];
			}
			//memcpy(values, other.values, sizeof(Optional<X>) * elementCount);
		}
		else
		{
			values = nullptr;
		}
	}
	NDimArray(const NDimArray &&other)
	{
		if (other.values != nullptr)
		{
			if (this->values != nullptr)
			{
				delete[] values;
				dimensions.clear();
				dimMult.clear();
			}
			for (int i = 0; i < order; i++)
			{
				dimensions[i] = other.dimensions[i];
				dimMult[i] = other.dimMult[i];
			}
			values = other.values;
			elementCount = other.elementCount;
		}
		else
		{
			values = nullptr;
		}
	}
	~NDimArray()
	{
		if (values != nullptr)
		{
			delete[] values;
		}
	}

	void Initialise(const vector<int> &dimensionsInit)
	{
		if (values != nullptr)
		{
			delete[] values;
			dimensions.clear();
			dimMult.clear();
		}
		order = dimensionsInit.size();
		elementCount = 1;
		for (int i = 0; i < order; i++)
		{
			dimMult.push_back(elementCount);
			elementCount *= dimensionsInit[i];
			dimensions.push_back(dimensionsInit[i]);
		}
		values = new Optional<X>[elementCount];
	}

private:
	inline int GetMemoryIndex(const vector<int> &indices)
	{
		assert(indices.size() == order);
		assert(values != nullptr);
		int index = 0;
		for (int i = 0; i < order; i++)
		{
			index += indices[i] * dimMult[i];
		}
		return index;
	}

	bool AreIndicesValid(const vector<int> &indices)
	{
		assert(indices.size() == order);
		for (int i = 0; i < order; i++)
		{
			if (indices[i] < 0 || indices[i] >= this->dimensions[i])
			{
				return false;
			}
		}
		return true;
	}

public:
	bool IsDefined(const vector<int> &indices)
	{
		assert(AreIndicesValid(indices));
		return values[GetMemoryIndex(indices)].IsValid();
	}

	//Danger function! Only use this if you're sure the value exists (check with IsDefined())
	// - if it's not this function will cause an assertion fail!
	X GetRaw(const vector<int> &indices)
	{
		assert(AreIndicesValid(indices));
		return values[GetMemoryIndex(indices)].GetValue();
	}
	Optional<X> GetOptional(const vector<int> &indices)
	{
		assert(AreIndicesValid(indices));
		return values[GetMemoryIndex(indices)];
	}

	void Set(const vector<int> &indices, X value)
	{
		assert(AreIndicesValid(indices));
		values[GetMemoryIndex(indices)] = Optional<X>(value);
	}
	void Clear(const vector<int> &indices)
	{
		assert(AreIndicesValid(indices));
		values[GetMemoryIndex(indices)] = Optional<X>();
	}

	void ForEach(const function<void(X)>& inputFunction)
	{
		for (unsigned int i = 0; i<elementCount; i++)
		{
			if (values[i].IsValid())
			{
				inputFunction(values[i].GetValue());
			}
		}
	}
};