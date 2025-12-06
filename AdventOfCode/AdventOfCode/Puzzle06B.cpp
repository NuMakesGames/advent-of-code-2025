#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle06B
{
	// 9630000828442
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto total = 0ull;

		// Parse everything into a 2d grid, preserving space characters
		auto grid = ConvertLinesToGrid(inputLines);

		// For each operand...
		auto xOperand = 0;
		while (xOperand < grid.Width())
		{
			// Find the next operand or the end of the grid
			auto xNextOperand = xOperand + 1;
			while (xNextOperand < grid.Width() && grid.at(xNextOperand, grid.Height() - 1) == ' ')
			{
				++xNextOperand;
			}

			// Then parse the terms, top-to-bottom, right-to-left
			std::vector<int64_t> terms;
			auto xFirstTerm = xNextOperand == grid.Width() ? grid.Width() - 1 : xNextOperand - 2; // no trailing space on last column
			for (int x = xFirstTerm; x >= xOperand; --x)
			{
				auto currentTerm = 0;
				for (auto y = 0; y < grid.Height() - 1; ++y)
				{
					char c = grid.at(x, y);
					if (c == ' ')
					{
						continue;
					}

					currentTerm *= 10;
					currentTerm += c - '0';
				}
				terms.emplace_back(currentTerm);
			}

			// Solve the equation
			auto operand = grid.at(xOperand, grid.Height() - 1);
			if (operand == '+')
			{
				auto sum = 0ull;
				for (auto term : terms)
				{
					sum += term;
				}
				total += sum;
			}
			else
			{
				auto product = 1ull;
				for (auto term : terms)
				{
					product *= term;
				}
				total += product;
			}

			//Advance to the next operand
			xOperand = xNextOperand;
		}

		return std::to_string(total);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle06B