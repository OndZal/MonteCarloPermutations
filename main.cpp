#include <iostream>
#include <string>
#include <vector>
#include <string_view>
#include <charconv>
#include "permutation.hpp"
#include "monte_carlo.hpp"

// the main function handles the input and output format
// converts its arguments to numbers and permutation objects
int main(int argc, char** argv)
{
	if (argc != 4)
	{
		std::cout << "expect three arguments: <pattern> <length> <number of steps>";
	}
	else
	{
		std::string pattern_string(argv[1]);
		std::string_view pattern_view(pattern_string);
		std::vector<unsigned> pattern_values;
		
		while (pattern_view.size() > 0)
		{
			auto next_delimiter = pattern_view.find(',');
			if (next_delimiter == std::string_view::npos)
				next_delimiter = pattern_view.size();

			unsigned next_value;
			auto conversion_result = std::from_chars(pattern_view.data(), pattern_view.data() + next_delimiter, next_value);

			if (conversion_result.ec == std::errc::invalid_argument || conversion_result.ec == std::errc::result_out_of_range)
			{
				std::cout << "incorrect pattern format";
				exit(0);
			}

			pattern_values.push_back(next_value);

			if (next_delimiter < pattern_view.size())
				pattern_view.remove_prefix(next_delimiter + 1);
			else
				pattern_view.remove_prefix(pattern_view.size());
		}

		auto pattern = permutation::convert_to_permutation(pattern_values);
		
		if (pattern.has_value())
		{
			auto result = markov_chain_monte_carlo(*pattern, std::stoi(argv[2]), std::stoi(argv[3]));

			for (size_t i = 0; i < result.size(); i++)
			{
				std::cout << result[i] << ' ';
			}
			std::cout << std::endl;
		}
		else
			std::cout << "incorrect pattern format";
	}
}
