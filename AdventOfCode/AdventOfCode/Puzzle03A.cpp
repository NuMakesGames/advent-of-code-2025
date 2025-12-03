#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle03A
{
	// 17113
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto result = 0ull;

		auto banks = std::vector<std::vector<int32_t>>{};
		for (const auto& line : inputLines)
		{
			std::vector<int> bank;
			for (char c : line)
			{
				bank.emplace_back(c - '0');
			}
			banks.emplace_back(bank);
		}

		int jolts = 0;
		for (const auto& bank : banks)
		{
			int firstIndex = 0;
			int firstBattery = bank[firstIndex];
			for (int i = 1; i < bank.size() - 1; ++i)
			{
				if (bank[i] > firstBattery)
				{
					firstIndex = i;
					firstBattery = bank[i];
				}
			}

			int secondIndex = firstIndex + 1;
			int secondBattery = bank[secondIndex];
			for (int j = secondIndex; j < bank.size(); ++j)
			{
				if (bank[j] > secondBattery)
				{
					secondIndex = j;
					secondBattery = bank[j];
				}
			}

			jolts += firstBattery * 10 + secondBattery;
		}

		return std::to_string(jolts);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle03A