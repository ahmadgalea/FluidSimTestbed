#pragma once


//This feels like something that probably exists already, but it wasn't obvious to me where to find it.
//A simple container that doesn't do any heap allocations, is of fixed size, and you can easily add and delete
//stuff. NOT intended to be used in large sizes, and is fairly dumb - created for stuff like bunches of a dozen
//pointers or so, that kind of thing.

//Mostly for simple types - not much use in trying to keep stuff on the stack if it's doing its own allocations.

template <class TYPE, int SIZE>
class StackArray
{
private:
	TYPE values[SIZE];
	int valuesStored = 0;

public:
	StackArray() {}

	bool AddValue(TYPE value)
	{
		if (valuesStored < SIZE)
		{
			values[valuesStored] = value;
			valuesStored++;
			return true;
		}
		else
		{
			return false;
		}
	}

	TYPE operator[](int index)
	{
		if (index >= valuesStored)
		{
			throw "StackArray out of bounds exception!";
		}
		return values[index];
	}

	//This will remove the first instance of this value in the array, and shuffle the rest along.
	bool DeleteSingleValue(TYPE targetForDeletion)
	{
		int i = 0;
		bool valueFound = false;
		while (i < valuesStored)
		{
			if (targetForDeletion == values[i])
			{
				valueFound = true;
				valuesStored--;
				break;
			}
			i++;
		}

		while (i < valuesStored - 1)
		{
			values[i] = values[i + 1];
			i++;
		}
		return valueFound;
	}

	int CurrentSize()
	{
		return valuesStored;
	}

	int MaxSize()
	{
		return SIZE;
	}
};