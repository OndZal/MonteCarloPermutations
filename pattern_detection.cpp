#include "pattern_detection.hpp"
#include <vector>

// positions is a vector of unique indices less than or equal to max_index
// increments the highest index possible and sets the following indices right after it
// returns true if the function found the next tuple and modified the vector
// returns false if all the indices were at their maximum, vector is unmodified
bool next_tuple(std::vector<unsigned>& positions, unsigned max_index)
{
	// tries for each index starting from the last
	// i needs to be signed to compare to 0 properly
	for (long i = positions.size() - 1; i >= 0; i--)
	{
		// if either there is a gap between positions[i] and positions[i + 1] (and positions[i + 1] exists)
		// or if there is a gap between the last position in the tuple and max_index
		if ((i < positions.size() - 1 && positions[i] < positions[i + 1] - 1) || (i == positions.size() - 1 && positions[i] < max_index))
		{
			positions[i]++;

			// set the following positions to immediately follow positions[i]
			for (unsigned j = i + 1; j < positions.size(); j++)
			{
				positions[j] = positions[i] + j - i;
			}

			return true;
		}
	}

	// if none of the increments was possible the positions were set on the last indices and cannot be set further
	return false;
}

// searches all k-tuples (where k is the length of pattern) of positions in the base permutation
// and checks whether any of them matches the pattern
// returns true if perm contains pattern
// assumes perm.size() >= pattern.size()
bool exhaustive_search(const permutation& perm, const permutation& pattern)
{
	// represents the indices of the k-tuple to be matched against the pattern
	std::vector<unsigned> positions(pattern.size());

	// set up the inital positions as the first ones
	for (unsigned i = 0; i < positions.size(); i++)
	{
		positions[i] = i;
	}
	bool select_succes = true;

	// while new tuples to check are found
	while (select_succes)
	{
		// check the positions for the pattern
		bool matching = true;
		for (unsigned i = 0; i < positions.size(); i++)
		{
			for (unsigned j = 0; j < i; j++)
			{
				// checks if the ordering of elements on the i-th and j-th positions of the tuple matches the pattern
				// depends on uniqueness of the elements of permutations, doesn't consider equality
				if ((pattern[j] > pattern[i]) != (perm[positions[j]] > perm[positions[i]]))
				{
					matching = false;
					break;
				}
			}

			// if the tuple doesn't match up to position i, skip checking the remaining positions
			if (!matching)
				break;
		}

		if (matching)
			return true;

		// select next tuple
		select_succes = next_tuple(positions, perm.size() - 1);
		
	}
	return false;
}

// checks if the permutation perm contains the permutation pattern given by pattern
// main point of expansion/optimisation, selects algorithms for special cases
bool contains_pattern(const permutation& perm, const permutation& pattern)
{
	if (perm.size() >= pattern.size())
		return exhaustive_search(perm, pattern);
	else
		return false;
}