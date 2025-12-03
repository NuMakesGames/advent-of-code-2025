#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle02A
{
	constexpr std::array<uint64_t, 14> powers = {
		1,          10,          100,           1'000,          10'000,          100'000,           1'000'000,
		10'000'000, 100'000'000, 1'000'000'000, 10'000'000'000, 100'000'000'000, 1'000'000'000'000, 10'000'000'000'000
	};

	std::tuple<uint64_t, uint64_t, uint64_t> FindNextInvalidId(const std::string& idStr)
	{
		auto id = std::stoull(idStr);
		auto pattern = 0ull;
		auto minDigits = idStr.size();
		if (minDigits % 2 != 0)
		{
			minDigits = minDigits + 1;
			pattern = powers[minDigits / 2 - 1];
		}
		else
		{
			for (auto i = 0; i < idStr.size() / 2; ++i)
			{
				pattern = pattern * 10 + (idStr[i] - '0');
			}
		}

		auto invalidId = pattern * powers[minDigits / 2] + pattern;
		while (invalidId < id)
		{
			pattern++;
			invalidId = pattern * powers[minDigits / 2] + pattern;
		}

		return std::make_tuple(invalidId, pattern, minDigits);
	}

	std::pair<uint64_t, uint64_t> FindPreviousInvalidId(const std::string& idStr)
	{
		auto id = std::stoull(idStr);
		auto maxDigits = idStr.size();
		if (maxDigits % 2 != 0)
		{
			maxDigits = maxDigits + - 1;
		}
	
		auto pattern = powers[maxDigits / 2] - 1;
		auto invalidId = pattern * powers[maxDigits / 2] + pattern;
		while (invalidId > id)
		{
			pattern--;
			invalidId = pattern * powers[maxDigits / 2] + pattern;
		}

		return std::make_pair(invalidId, pattern);
	}

	// 8576933996
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto productRanges = Utilities::SplitString(inputLines[0], ",");
		auto total = 0ull;
		for (const auto& productRange : productRanges)
		{
			auto bounds = Utilities::SplitString(productRange, "-");
			auto firstId = bounds[0];
			auto lastId = bounds[1];
			auto [firstInvalidId, firstPattern, minDigits] = FindNextInvalidId(firstId);
			auto [lastInvalidId, lastPattern] = FindPreviousInvalidId(lastId);
			if (firstInvalidId > lastInvalidId)
			{
				continue;
			}

			auto sum = lastPattern * (lastPattern + 1) / 2 - (firstPattern - 1) * firstPattern / 2;
			auto multiplier = powers[minDigits / 2] + 1; 
			total += sum * multiplier;
		}

		return std::to_string(total);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle02A