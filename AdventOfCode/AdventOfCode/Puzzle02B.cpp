#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle02B
{
	// 25663320831
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto productRanges = Utilities::SplitString(inputLines[0], ",");
		std::unordered_set<uint64_t> invalidIds;
		for (const auto& productRange : productRanges)
		{
			auto bounds = Utilities::SplitString(productRange, "-");
			for (auto id = std::stoull(bounds[0]); id <= std::stoull(bounds[1]); ++id)
			{
				std::string str = std::to_string(id);
				for (auto repeats = 2; repeats <= str.size(); ++repeats)
				{
					bool isInvalid = true;
					if (str.size() % repeats != 0)
					{
						continue;
					}

					auto stride = str.size() / repeats;
					for (auto i = 0; i < stride; ++i)
					{
						auto next = i + stride;
						while (next < str.size())
						{
							if (str[i] != str[next])
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
		}

		return std::to_string(std::accumulate(invalidIds.begin(), invalidIds.end(), 0ull));
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle02B