#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle01A
{
	// 1147
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		int dial = 50;
		int numZeros = 0;
		for (const auto& line : inputLines)
		{
			// Extract rotations
			int totalRotation = 0;
			for (int i = 1; i < line.size(); ++i)
			{
				totalRotation *= 10;
				totalRotation += line[i] - '0';
			}

			// Turn the dial left or right based on instruction
			constexpr int numDialValues = 100;
			int partialRotation = totalRotation % numDialValues;
			if (line[0] == 'L')
			{
				dial -= partialRotation;
				if (dial < 0)
				{
					dial += numDialValues;
				}
			}
			else
			{
				dial += partialRotation;
				if (dial > numDialValues - 1)
				{
					dial -= numDialValues;
				}
			}

			// Count if the dial ended on zero
			if (dial == 0)
			{
				++numZeros;
			}
		}

		return std::to_string(numZeros);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle01A