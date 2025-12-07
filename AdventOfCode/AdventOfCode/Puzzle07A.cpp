#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle07A
{
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto grid = ConvertLinesToGrid(inputLines);
		auto beamIndices = std::vector<int>{};
		for (int i = 0; i < inputLines[0].size(); ++i)
		{
			if (inputLines[0][i] == 'S')
			{
				beamIndices.emplace_back(i);
				break;
			}
		}

		auto totalSplits = 0ull;
		for (auto y = 0; y < grid.Height(); ++y)
		{
			auto nextBeamIndices = std::vector<int>{};
			for (auto x : beamIndices)
			{
				constexpr auto down = Vector2d<int>{ 0, 1 };
				auto next = Vector2d<int>{ x, y } + down;
				if (!grid.IsInBounds(next))
				{
					continue;
				}

				auto c = grid.at(next);
				switch (c)
				{
					case '.':
						grid.at(next) = '|';
						nextBeamIndices.emplace_back(next.x);
						break;
					case '^':
						constexpr auto left = Vector2d<int>{ -1, 0 };
						auto nextLeft = next + left;
						if (grid.IsInBounds(nextLeft))
						{
							grid.at(nextLeft) = '|';
							nextBeamIndices.emplace_back(nextLeft.x);
						}

						constexpr auto right = Vector2d<int>{ 1, 0 };
						auto nextRight = next + right;
						if (grid.IsInBounds(nextRight))
						{
							grid.at(nextRight) = '|';
							nextBeamIndices.emplace_back(nextRight.x);
						}

						++totalSplits;
						break;
				}
			}

			beamIndices.swap(nextBeamIndices);
		}

		return std::to_string(totalSplits);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle07A