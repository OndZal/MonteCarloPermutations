#include "permutation.hpp"

std::optional<permutation> permutation::convert_to_permutation(const std::vector<unsigned>& values)
{
	permutation result(values.size());

	// because index goes from 0 to size - 1 and a permutation goes from 1 to size,
	// seen[index] stores whether the value index + 1 was already encountered in values
	std::vector<bool> seen(values.size());

	for (unsigned i = 0; i < values.size(); i++)
	{
		if (values[i] > 0 && values[i] <= values.size())
		{
			// convert to zero based index
			if (seen[values[i] - 1])
				return std::nullopt;

			seen[values[i] - 1] = true;
			result.elems_[i] = values[i];
		}
		else
			return std::nullopt;
	}

	// if all the values were unique and in range, values was a correct permutation
	// checking seen not required
	return result;
}