#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle01B
{
	// 6789
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

			// Full rotations always cross zero
			constexpr int numDialValues = 100;
			auto fullRotations = totalRotation / numDialValues;
			numZeros += fullRotations;

			// Turn the dial left or right based on instruction
			auto remainingRotation = totalRotation % numDialValues;
			if (line[0] == 'L')
			{
				if (dial == 0)
				{
					// Left turn started from zero; don't double count this zero when wrapping
					dial -= remainingRotation;
					dial += numDialValues;
				}
				else
				{
					dial -= remainingRotation;
					if (dial == 0)
					{
						// Left turn stopped on zero
						++numZeros;
					}
					else if (dial < 0)
					{
						// Left turn crossed zero
						++numZeros;
						dial += numDialValues;
					}
				}
			}
			else
			{
				dial += remainingRotation;
				if (dial > numDialValues - 1)
				{
					// Right turn crossed zero
					dial -= numDialValues;
					++numZeros;
				}
			}
		}

		return std::to_string(numZeros);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle01B