#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle02A
{
	// 8576933996
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto productRanges = Utilities::SplitString(inputLines[0], ",");
		std::unordered_set<uint64_t> invalidIds;
		for (const auto& productRange : productRanges)
		{
			auto bounds = Utilities::SplitString(productRange, "-");
			for (auto id = std::stoull(bounds[0]); id <= std::stoull(bounds[1]); ++id)
			{
				std::string idStr = std::to_string(id);
				if (idStr.size() % 2 != 0)
				{
					continue;
				}

				bool isInvalid = true;
				for (auto i = 0; i < idStr.size() / 2; ++i)
				{
					if (idStr[i] != idStr[idStr.size() / 2 + i])
					{
						isInvalid = false;
						break;
					}
				}

				if (isInvalid)
				{
					invalidIds.insert(id);
				}
			}
		}

		return std::to_string(std::accumulate(invalidIds.begin(), invalidIds.end(), 0ull));
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle02A