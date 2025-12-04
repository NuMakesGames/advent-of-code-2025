#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle04A
{
	// 1428
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		constexpr std::array<Vector2d<int>, 8> adjacentDirections{
			Vector2d<int>{ -1, 0 },  Vector2d<int>{ 1, 0 },  Vector2d<int>{ 0, -1 }, Vector2d<int>{ 0, 1 },
			Vector2d<int>{ -1, -1 }, Vector2d<int>{ 1, -1 }, Vector2d<int>{ -1, 1 }, Vector2d<int>{ 1, 1 },
		};

		auto grid = Utilities::ConvertLinesToGrid(inputLines);
		auto reachableRolls = 0ull;
		for (auto y = 0; y < grid.Height(); ++y)
		{
			for (auto x = 0; x < grid.Width(); ++x)
			{
				if (grid.at(x, y) != '@')
				{
					continue;
				}

				auto adjacentRolls = 0;
				for (const auto& direction : adjacentDirections)
				{
					if (grid.IsInBounds(x + direction.x, y + direction.y) && grid.at(x + direction.x, y + direction.y) == '@')
					{
						++adjacentRolls;
					}
				}

				if (adjacentRolls < 4)
				{
					++reachableRolls;
				}
			}
		}

		return std::to_string(reachableRolls);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle04A