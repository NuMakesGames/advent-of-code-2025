#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle12A
{
	// 555
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto iLine = 0;
		auto sizes = std::vector<uint8_t>{};
		while (!inputLines[iLine].contains('x'))
		{
			++iLine;
			auto size = 0;
			for (auto i = 0; i < 3; ++i)
			{

				if (inputLines[iLine][i] == '#')
				{
					++size;
				}

				if (inputLines[iLine + 1][i])
				{
					++size;
				}

				if (inputLines[iLine + 2][i])
				{
					++size;
				}
			}
			sizes.emplace_back(size);
			iLine += 4;
		}

		auto regions = 0ull;
		for (; iLine < inputLines.size(); ++iLine)
		{
			auto tokens = Utilities::SplitString(inputLines[iLine], ": ");
			auto dimensions = ExtractInt64s(tokens[0]);
			auto presentCounts = ExtractInt64s(tokens[1]);

			auto requiredArea = 0ll;
			for (auto i = 0; i < sizes.size(); ++i)
			{
				requiredArea += presentCounts[i] * sizes[i];
			}

			if ((dimensions[0] * dimensions[1]) >= static_cast<int64_t>(requiredArea))
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