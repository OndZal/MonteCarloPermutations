#ifndef __MC_STEP_HPP__
#define __MC_STEP_HPP__
#include "permutation.hpp"
#include "pattern_detection.hpp"
#include <random>

// assumes permutation doesn't contain pattern
// randomly picks a change in the permutation
// and if the changed permutation doesn't contain pattern the change is applied to perm
// recieves the random number generator as an argument to avoid reseeding it
// RNG requires:
//	to satisfy UniformRandomBitGenerator to be usable for std::uniform_int_distribution
template<typename RNG>
void monte_carlo_step(permutation& perm, const permutation& pattern, RNG& random_index)
{
	std::uniform_int_distribution<unsigned> uniform(0, perm.size() - 1);

	auto index1 = uniform(random_index);
	auto index2 = uniform(random_index);

	// the source article speaks about insetrion rather than swapping
	// but swapping is faster and the properties of the markov chain should still hold
	perm.swap_positions(index1, index2);

	if (contains_pattern(perm, pattern))
	{
		// if the new permutation contains pattern, revert the change
		perm.swap_positions(index1, index2);
	}
}

// the main function that does everything after input conversion
// mostly loops monte_carlo_step
// returns a permutation avoiding forbidden_pattern of size "size"
permutation markov_chain_monte_carlo(const permutation& forbidden_pattern, unsigned size, size_t step_count);
#endif // !__MC_STEP_HPP__

