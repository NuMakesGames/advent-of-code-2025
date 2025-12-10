#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle09B
{
	// 1461987144
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto points = std::vector<Vector2d<int>>{};
		for (const auto& line : inputLines)
		{
			auto coords = ExtractInts<int>(line);
			points.emplace_back(coords[0], coords[1]);
		}

		// Build perimeter...
		std::unordered_set<Vector2d<int>> perimeter;
		for (auto i = 0; i < points.size(); ++i)
		{
			const auto& first = points[i];
			const auto& second = points[i == points.size() - 1 ? 0 : i + 1];

			if (first.x == second.x)
			{
				auto start = std::min(first.y, second.y);
				auto end = std::max(first.y, second.y);
				for (auto y = start; y <= end; ++y)
				{
					perimeter.insert(Vector2d<int>{ first.x, y });
				}
			}
			else
			{
				auto start = std::min(first.x, second.x);
				auto end = std::max(first.x, second.x);
				for (auto x = start; x <= end; ++x)
				{
					perimeter.insert(Vector2d<int>{ x, first.y });
				}
			}
		}

		// Compute all rectangles
		auto allRectangles = std::vector<std::tuple<uint64_t, Vector2d<int>, Vector2d<int>>>{};
		for (auto i = 0; i < points.size() - 1; ++i)
		{
			for (auto j = i + 1; j < points.size(); ++j)
			{
				uint64_t dx = std::abs(points[i].x - points[j].x) + 1;
				uint64_t dy = std::abs(points[i].y - points[j].y) + 1;
				uint64_t area = dx * dy;
				allRectangles.emplace_back(area, points[i], points[j]);
			}
		}
		std::ranges::sort(allRectangles, std::greater<std::tuple<uint64_t, Vector2d<int>, Vector2d<int>>>{});

		// Find largest valid rectangle by tracing interior
		auto maxArea = 0ll;
		auto maxPoints = std::pair<Vector2d<int>, Vector2d<int>>{};
		for (const auto& [area, firstPoint, secondPoint] : allRectangles)
		{
			auto minX = std::min(firstPoint.x, secondPoint.x) + 1;
			auto maxX = std::max(firstPoint.x, secondPoint.x) - 1;
			auto minY = std::min(firstPoint.y, secondPoint.y) + 1;
			auto maxY = std::max(firstPoint.y, secondPoint.y) - 1;

			auto isValid = true;
			for (auto x = minX; x <= maxX; ++x)
			{
				if (perimeter.contains(Vector2d<int>{ x, minY }) || perimeter.contains(Vector2d<int>{ x, maxY }))
				{
					isValid = false;
					break;
				}
			}

			if (!isValid)
			{
				continue;
			}

			for (auto y = minY; y <= maxY; ++y)
			{
				if (perimeter.contains(Vector2d<int>{ minX, y }) || perimeter.contains(Vector2d<int>{ maxX, y }))
				{
					isValid = false;
					break;
				}
			}

			if (!isValid)
			{
				continue;
			}

			maxArea = area;
			maxPoints = std::make_pair(firstPoint, secondPoint);
			break;
		}

		return std::to_string(maxArea);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle09B