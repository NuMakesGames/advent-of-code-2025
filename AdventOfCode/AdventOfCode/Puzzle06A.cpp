#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle06A
{
	// 5977759036837
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto terms = std::vector<std::vector<int64_t>>{};
		for (auto i = 0; i < inputLines.size() - 1; ++i)
		{
			terms.push_back(ExtractInt64s(inputLines[i]));;
		}

		auto operands = std::vector<char>{};
		for (auto c : inputLines.back())
		{
			if (c == ' ')
			{
				continue;
			}

			operands.emplace_back(c);
		}

		auto total = 0ull;
		for (auto col = 0; col < operands.size(); ++col)
		{
			if (operands[col] == '+')
			{
				auto sum = 0ull;
				for (auto& term : terms)
				{
					sum += term[col];
				}
				total += sum;
			}
			else
			{
				auto product = 1ull;
				for (auto & term : terms)
				{
					product *= term[col];
				}
				total += product;
			}
		}

		return std::to_string(total);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle06A