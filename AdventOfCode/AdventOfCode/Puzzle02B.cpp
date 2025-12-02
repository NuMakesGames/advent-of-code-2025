#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle02B
{
	std::unordered_set<uint64_t> FindInvalidIds(uint64_t firstId, uint64_t lastId)
	{
		std::unordered_set<uint64_t> invalidIds;
		for (auto id = firstId; id <= lastId; ++id)
		{
			std::string idStr = std::to_string(id);
			for (auto repeats = 2; repeats <= idStr.size(); ++repeats)
			{
				bool isInvalid = true;
				if (idStr.size() % repeats != 0)
				{
					continue;
				}

				auto stride = idStr.size() / repeats;
				for (auto i = 0; i < stride; ++i)
				{
					auto next = i + stride;
					while (next < idStr.size())
					{
						if (idStr[i] != idStr[next])
						{
							isInvalid = false;
							break;
						}
						next += stride;
					}
				}

				if (isInvalid)
				{
					invalidIds.insert(id);
				}
			}
		}

		return invalidIds;
	}

	// 25663320831
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto productRanges = Utilities::SplitString(inputLines[0], ",");
		auto futures = std::vector<std::future<std::unordered_set<uint64_t>>>{};
		futures.reserve(productRanges.size());

		for (const auto& productRange : productRanges)
		{
			auto bounds = Utilities::SplitString(productRange, "-");
			auto firstId = std::stoull(bounds[0]);
			auto lastId = std::stoull(bounds[1]);
			futures.push_back(std::async(std::launch::async, FindInvalidIds, firstId, lastId));
		}

		std::unordered_set<uint64_t> invalidIds;
		for (auto& future : futures)
		{
			auto result = future.get();
			invalidIds.insert_range(result);
		}

		return std::to_string(std::accumulate(invalidIds.begin(), invalidIds.end(), 0ull));
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle02B