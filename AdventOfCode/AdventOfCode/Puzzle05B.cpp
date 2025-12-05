#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle05B
{
	struct IngredientRange
	{
		uint64_t start = 0;
		uint64_t end = 0;

		auto operator<=>(const IngredientRange&) const = default;
	};

	// 333892124923577
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		// Parse fresh ingredient ranges
		std::vector<IngredientRange> ingredientRanges;
		for (auto i = 0; i < inputLines.size(); ++i)
		{
			const auto& line = inputLines[i];
			if (line.empty())
			{
				break;
			}

			auto ingredients = Utilities::SplitString(line, "-");
			ingredientRanges.emplace_back(std::stoull(ingredients[0]), std::stoull(ingredients[1]));
		}

		// Merge all ranges in-place
		std::ranges::sort(ingredientRanges);
		auto iCurrent = 0;
		for (auto iNext = 1; iNext < ingredientRanges.size(); ++iNext)
		{
			IngredientRange& current = ingredientRanges[iCurrent];
			const IngredientRange& next = ingredientRanges[iNext];

			if (next.start <= current.end)
			{
				current.end = std::max(current.end, next.end);
			}
			else
			{
				ingredientRanges[++iCurrent] = next;
			}
		}
		ingredientRanges.resize(iCurrent + 1);

		// Count the total fresh ingredients
		auto totalFreshIngredients = std::accumulate(
			ingredientRanges.cbegin(),
			ingredientRanges.cend(),
			0ull,
			[](uint64_t acc, const IngredientRange& r) { return acc + r.end - r.start + 1; });

		return std::to_string(totalFreshIngredients);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle05B