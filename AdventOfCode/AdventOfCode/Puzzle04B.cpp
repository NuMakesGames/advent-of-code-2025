#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;
using namespace std::chrono_literals;

namespace Puzzle04B
{
	// 8936
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		constexpr std::array<Vector2d<int>, 8> adjacentDirections{
			Vector2d<int>{ -1, 0 },  Vector2d<int>{ 1, 0 },  Vector2d<int>{ 0, -1 }, Vector2d<int>{ 0, 1 },
			Vector2d<int>{ -1, -1 }, Vector2d<int>{ 1, -1 }, Vector2d<int>{ -1, 1 }, Vector2d<int>{ 1, 1 },
		};

		auto grid = Utilities::ConvertLinesToGrid(inputLines);
		auto rollsRemovedLastIteration = 0ull;
		auto totalRollsRemoved = 0ull;
		do
		{
			rollsRemovedLastIteration = totalRollsRemoved;
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
						++totalRollsRemoved;
						grid.at(x, y) = '.';
					}
				}
			}
		}
		while (totalRollsRemoved != rollsRemovedLastIteration);

		return std::to_string(totalRollsRemoved);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		constexpr std::array<Vector2d<int>, 8> adjacentDirections{
			Vector2d<int>{ -1, 0 },  Vector2d<int>{ 1, 0 },  Vector2d<int>{ 0, -1 }, Vector2d<int>{ 0, 1 },
			Vector2d<int>{ -1, -1 }, Vector2d<int>{ 1, -1 }, Vector2d<int>{ -1, 1 }, Vector2d<int>{ 1, 1 },
		};

		auto grid = Utilities::ConvertLinesToGrid(inputLines);
		ConsoleRenderer renderer;
		renderer.SetIncrementalDrawingEnabled(true);
		for (auto y = 0; y < grid.Height() && y < renderer.GetHeight(); ++y)
		{
			for (auto x = 0; x < grid.Width() && x < renderer.GetWidth(); ++x)
			{
				char c = grid.at(x, y);
				renderer.DrawChar(x, y, c, c == '@' ? color::ForegroundBrightCyan : color::ForegroundWhite);
			}
		}
		renderer.Present();

		auto rollsRemovedLastIteration = 0ull;
		auto totalRollsRemoved = 0ull;
		do
		{
			rollsRemovedLastIteration = totalRollsRemoved;
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
						++totalRollsRemoved;
						grid.at(x, y) = '.';
						renderer.DrawChar(x, y, 'x', color::ForegroundBrightRed);
						renderer.Present();
						std::this_thread::sleep_for(1ms);
					}
				}
			}
		}
		while (totalRollsRemoved != rollsRemovedLastIteration);

		std::this_thread::sleep_for(1s);
		return std::to_string(totalRollsRemoved);
	}
} // namespace Puzzle04B