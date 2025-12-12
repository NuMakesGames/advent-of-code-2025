#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle12A
{
	Grid2d<char> Rotate90(const Grid2d<char>& grid)
	{
		auto result = Grid2d<char>{ 3, 3 };
		for (auto y = 0; y < 3; ++y)
		{
			for (auto x = 0; x < 3; ++x)
			{
				result.at(x, y) = grid.at(2 - y, x);
			}
		}
		return result;
	}

	std::vector<Grid2d<char>> FindPresentPlacements(const Grid2d<char>& region, const Grid2d<char>& present)
	{
		auto validPlacements = std::vector<Grid2d<char>>{};
		for (auto y = 0; y < region.Height() - 3; ++y)
		{
			for (auto x = 0; x < region.Width() - 3; ++x)
			{
				bool isValid = true;
				auto newRegion = region;
				for (auto q = 0; q < 3; ++q)
				{
					for (auto p = 0; p < 3; ++p)
					{
						auto c = present.at(p, q);
						if (c == '#' && region.at(x + p, y + q) != '.')
						{
							isValid = false;
							break;
						}
						else
						{
							newRegion.at(x + p, y + q) = c;
						}
					}

					if (!isValid)
					{
						break;
					}
				}

				if (isValid)
				{
					validPlacements.emplace_back(std::move(newRegion));
				}
			}
		}
		return validPlacements;
	}

	bool TestRegion(
		const std::vector<std::vector<Grid2d<char>>>& presentVariants,
		const std::vector<int>& presentCounts,
		const Grid2d<char>& region)
	{
		if (std::ranges::all_of(presentCounts, [](int presentCount) {  return presentCount == 0; }))
		{
			return true;
		}

		for (auto i = 0; i < presentCounts.size(); ++i)
		{
			const auto& count = presentCounts[i];
			if (count == 0)
			{
				continue;
			}

			auto nextPresentCounts = presentCounts;
			nextPresentCounts[i]--;
			for (const auto& present : presentVariants[i])
			{
				for (const auto& newRegion : FindPresentPlacements(region, present))
				{
					if (TestRegion(presentVariants, nextPresentCounts, newRegion))
					{
						return true;
					}
				}
			}
		}

		return false;
	}

	bool TestRegion(const std::vector<std::vector<Grid2d<char>>>& presentVariants, const std::vector<int>& presentCounts, const std::vector<int>& dimensions)
	{
		auto region = Grid2d<char>{ dimensions[0], dimensions[1] };
		std::ranges::fill(region, '.');
		return TestRegion(presentVariants, presentCounts, region);
	}

	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto iLine = 1;
		auto presents = std::vector<Grid2d<char>>{};
		while (!inputLines[iLine].contains('x'))
		{
			auto present = Grid2d<char>{ 3, 3 };
			for (auto i = 0; i < 3; ++i)
			{
				present.at(i, 0) = inputLines[iLine][i];
				present.at(i, 1) = inputLines[iLine + 1][i];
				present.at(i, 2) = inputLines[iLine + 2][i];
			}
			presents.emplace_back(std::move(present));
			iLine += 5;
		}

		auto presentVariants = std::vector<std::vector<Grid2d<char>>>{};
		for (const auto& present : presents)
		{
			auto current = std::vector<Grid2d<char>>{};
			current.emplace_back(present);

			auto next = Rotate90(present);
			if (std::ranges::find(current, next) == current.end())
			{
				current.emplace_back(next);
			}

			next = Rotate90(next);
			if (std::ranges::find(current, next) == current.end())
			{
				current.emplace_back(next);
			}

			next = Rotate90(next);
			if (std::ranges::find(current, next) == current.end())
			{
				current.emplace_back(next);
			}

			presentVariants.emplace_back(current);
		}

		auto regions = 0ull;
		for (; iLine < inputLines.size(); ++iLine)
		{
			auto tokens = Utilities::SplitString(inputLines[iLine], ": ");
			auto dimensions = ExtractInt32s(tokens[0]);
			auto presentCounts = ExtractInt32s(tokens[1]);
			if (TestRegion(presentVariants, presentCounts, dimensions))
			{
				++regions;
			}
		}

		return std::to_string(regions);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}


} // namespace Puzzle12A