#ifndef __PERMUTATION_HPP__
#define __PERMUTATION_HPP__
#include <vector>

class permutation
{
public:
	// returns the permutation (1,2,3,...,size - 1,size)
	// used as inital pemutation that avoids any pattern with a descending part
	static permutation get_ascending(unsigned size)
	{
		permutation result(size);

		for (unsigned i = 0; i < size; i++)
		{
			result.elems_[i] = i + 1;
		}

		return result;
	}

	//  returns the permutation (size,size - 1,size - 2,...,2,1)
	// used as inital pemutation that avoids any pattern with an ascending part
	static permutation get_descending(unsigned size)
	{
		permutation result(size);

		for (unsigned i = 0; i < size; i++)
		{
			result.elems_[i] = size - i;
		}

		return result;
	}

	unsigned operator[](unsigned index)
	{
		return elems_[index];
	}

	unsigned size()
	{
		return elems_.size();
	}

	void swap_positions(unsigned first, unsigned second)
	{
		unsigned tmp = elems_[first];
		elems_[first] = elems_[second];
		elems_[second] = tmp;
	}
private:
	permutation(unsigned size) : elems_(size) {}

	std::vector<unsigned> elems_;
};
#endif // !__PERMUTATION_HPP__

