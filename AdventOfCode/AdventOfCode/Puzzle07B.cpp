#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle07B
{
	uint64_t Recurse(const auto& grid, const Vector2d<int>& currentBeam)
	{
		static auto memoize = std::unordered_map<Vector2d<int>, uint64_t>{};
		if (memoize.contains(currentBeam))
		{
			return memoize[currentBeam];
		}

		if (currentBeam.y + 1 == grid.Height())
		{
			memoize[currentBeam] = 1;
			return 1;
		}

		auto result = 0ull;
		constexpr auto down = Vector2d<int>{ 0, 1 };
		auto next = currentBeam + down;
		auto c = grid.at(next);
		switch (c)
		{
			case '.':
				result = Recurse(grid, next);
				break;
			case '^':
				constexpr auto left = Vector2d<int>{ -1, 0 };
				constexpr auto right = Vector2d<int>{ 1, 0 };
				auto nextLeft = next + left;
				auto nextRight = next + right;
				if (grid.IsInBounds(nextLeft) && grid.IsInBounds(nextRight))
				{
					result = Recurse(grid, nextLeft) + Recurse(grid, nextRight);
				}
				else if (grid.IsInBounds(nextLeft))
				{
					result = Recurse(grid, nextLeft);
				}
				else if (grid.IsInBounds(nextRight))
				{
					result = Recurse(grid, nextRight);
				}
				break;
		}

		memoize[currentBeam] = result;
		return result;
	}

	// 24292631346665
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto grid = ConvertLinesToGrid(inputLines);
		auto startX = 0;
		for (int i = 0; i < inputLines[0].size(); ++i)
		{
			if (inputLines[0][i] == 'S')
			{
				startX = i;
				break;
			}
		}

		auto result = Recurse(grid, Vector2d<int>{ startX, 0 });
		return std::to_string(result);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle07B