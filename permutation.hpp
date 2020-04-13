#ifndef __PERMUTATION_HPP__
#define __PERMUTATION_HPP__
#include <vector>
#include <optional>

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

	// constructs a permutation object from values if the values represent a permutation
	// or returns an empty optional if the values aren't between 1 and values.size() or any of the values repeat
	static std::optional<permutation> convert_to_permutation(const std::vector<unsigned>& values);

	// other becomes an empty permutation of size 0
	permutation(permutation&& other) noexcept : elems_(std::move(other.elems_)) {}

	// other becomes an empty permutation of size 0
	permutation& operator=(permutation&& other) noexcept
	{
		elems_ = std::move(other.elems_);
		return *this;
	}

	unsigned operator[](unsigned index) const
	{
		return elems_[index];
	}

	unsigned size() const
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

