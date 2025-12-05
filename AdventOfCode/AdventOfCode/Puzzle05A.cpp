#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle05A
{
	struct IngredientRange
	{
		uint64_t start = 0;
		uint64_t end = 0;

		bool IsIngredientFresh(uint64_t v) const
		{
			return start <= v && v <= end;
		}
	};

	// 525
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		// Parse fresh ingredient ranges
		std::vector<IngredientRange> ingredientRanges;
		int i = 0;
		for (; i < inputLines.size(); ++i)
		{
			const auto& line = inputLines[i];
			if (line.empty())
			{
				++i;
				break;
			}

			auto ingredients = Utilities::SplitString(line, "-");
			ingredientRanges.emplace_back(std::stoull(ingredients[0]), std::stoull(ingredients[1]));
		}

		// Parse ingredients to check
		std::vector<uint64_t> ingredients;
		for (; i < inputLines.size(); ++i)
		{
			ingredients.emplace_back(std::stoull(inputLines[i]));
		}

		// Check for freshness
		auto freshIngredientCount = std::ranges::count_if(
			ingredients,
			[&ingredientRanges](uint64_t ingredient)
			{
				return std::ranges::any_of(
					ingredientRanges, [ingredient](const IngredientRange& r) { return r.IsIngredientFresh(ingredient); });
			});

		return std::to_string(freshIngredientCount);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle05A