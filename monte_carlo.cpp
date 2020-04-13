#include "monte_carlo.hpp"
#include <random>

permutation markov_chain_monte_carlo(const permutation& forbidden_pattern, unsigned size, size_t step_count)
{
	// initialize the first permutation
	permutation result(permutation::get_ascending(size));

	if (forbidden_pattern.size() > 1 && forbidden_pattern[0] < forbidden_pattern[1])
		// the pattern contains an ascending pair, the descending permutation avoids it
		result = permutation::get_descending(size);
	// else the pattern contains a descending pair, the ascending permutation avoids it

	// initialize the random number generation
	// @ add a debug mode with preset seed
	std::random_device seed;
	std::mt19937 rng(seed());

	for (size_t i = 0; i < step_count; i++)
	{
		monte_carlo_step(result, forbidden_pattern, rng);
	}

	return result;
}