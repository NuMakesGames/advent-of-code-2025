#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle09B
{
	struct Line
	{
		Vector2d<int> start;
		Vector2d<int> end;

		// Returns true if the line segments intersect
		bool Intersects(const Line& other) const
		{
			return Counterclockwise(start, other.start, other.end) != Counterclockwise(end, other.start, other.end)
			    && Counterclockwise(start, end, other.start) != Counterclockwise(start, end, other.end);
		}

		// Returns whether three points wind counterclockwise
		static bool Counterclockwise(const Vector2d<int>& a, const Vector2d<int>& b, const Vector2d<int>& c)
		{
			return static_cast<int64_t>(c.y - a.y) * static_cast<int64_t>(b.x - a.x)
			     > static_cast<int64_t>(b.y - a.y) * static_cast<int64_t>(c.x - a.x);
		}
	};

	// 1461987144
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto points = std::vector<Vector2d<int>>{};
		for (const auto& line : inputLines)
		{
			auto coords = ExtractInts<int>(line);
			points.emplace_back(coords[0], coords[1]);
		}

		// Build perimeter
		auto perimeter = std::vector<Line>{};
		for (auto i = 0; i < points.size(); ++i)
		{
			const auto& first = points[i];
			const auto& second = points[i == points.size() - 1 ? 0 : i + 1];
			perimeter.emplace_back(first, second);
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

		// Find largest valid rectangle by checking for intersections on internal perimeter of the rectangle
		auto maxArea = 0ll;
		auto maxPoints = std::pair<Vector2d<int>, Vector2d<int>>{};
		for (const auto& [area, firstPoint, secondPoint] : allRectangles)
		{
			auto minX = std::min(firstPoint.x, secondPoint.x) + 1;
			auto maxX = std::max(firstPoint.x, secondPoint.x) - 1;
			auto minY = std::min(firstPoint.y, secondPoint.y) + 1;
			auto maxY = std::max(firstPoint.y, secondPoint.y) - 1;

			// Create a rectangle inside the current rectangle
			auto innerPerimeter = std::array<Line, 4>{
				Line{ Vector2d<int>{ minX, minY }, Vector2d<int>{ maxX, minY } },
				Line{ Vector2d<int>{ minX, maxY }, Vector2d<int>{ maxX, maxY } },
				Line{ Vector2d<int>{ minX, minY }, Vector2d<int>{ minX, maxY } },
				Line{ Vector2d<int>{ maxX, minY }, Vector2d<int>{ maxX, maxY } },
			};

			// Test for intersetions using CCW test (https://bryceboe.com/2006/10/23/line-segment-intersection-algorithm/)
			auto isValid = true;
			for (const auto& innerLine : innerPerimeter)
			{
				for (const auto& outerLine : perimeter)
				{
					if (innerLine.Intersects(outerLine))
					{
						isValid = false;
						break;
					}
				}

				if (!isValid)
				{
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