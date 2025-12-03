#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle03B
{
	// 169709990062889
	std::string Solve(const std::vector<std::string>& inputLines)
	{
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

		int64_t totalJolts = 0;
		for (const auto& bank : banks)
		{
			constexpr int requiredBatteries = 12;
			std::vector<int> batteries;
			batteries.reserve(requiredBatteries);

			size_t minIndex = 0;
			while (batteries.size() < requiredBatteries)
			{
				for (int optimalBattery = 9; optimalBattery >= 1; --optimalBattery)
				{
					bool foundBattery = false;
					for (size_t i = minIndex; i <= bank.size() - (requiredBatteries - batteries.size()); ++i)
					{
						if (bank[i] == optimalBattery)
						{
							batteries.emplace_back(bank[i]);
							minIndex = i + 1;
							foundBattery = true;
							break;
						}
					}

					if (foundBattery)
					{
						break;
					}
				}
			}

			int64_t jolts = 0;
			for (auto battery : batteries)
			{
				jolts = jolts * 10 + battery;
			}

			totalJolts += jolts;
		}

		return std::to_string(totalJolts);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle03B