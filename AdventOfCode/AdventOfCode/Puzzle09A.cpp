#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle09A
{
	// 4767418746
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto points = std::vector<Vector2d<int64_t>>{};
		for (const auto& line : inputLines)
		{
			auto coords = ExtractInts<std::int64_t>(line);
			points.emplace_back(coords[0], coords[1]);
		}

		auto maxArea = 0ll;
		auto maxPoints = std::pair<Vector2d<int64_t>, Vector2d<int64_t>>{};
		for (auto i = 0; i < points.size() - 1; ++i)
		{
			for (auto j = i + 1; j < points.size(); ++j)
			{
				auto dx = std::abs(points[i].x - points[j].x) + 1;
				auto dy = std::abs(points[i].y - points[j].y) + 1;
				auto area = dx * dy;
				if (area > maxArea)
				{
					maxArea = area;
					maxPoints = std::make_pair(points[i], points[j]);
				}
			}
		}

		return std::to_string(maxArea);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle09A