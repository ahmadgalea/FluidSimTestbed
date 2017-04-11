#pragma once

//This is a class template for having a return value that might be invalid.
//It will replace some of the stuff that exceptions would otherwise do.

#include <assert.h>


template <class X>
class Optional
{
private:
	bool valid = false;
	X value;

public:
	Optional() {}

	Optional(X init) : value(init), valid(true) {}

	bool IsValid() const { return valid; }

	X GetValue() const
	{
		assert(valid);
		return value;
	}

	void SetValue(X val)
	{
		valid = true;
		value = val;
	}
};