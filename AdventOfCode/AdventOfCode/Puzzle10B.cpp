#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle10B
{
	struct State
	{
		std::array<int, 10> joltageLevels;
		size_t nextButton = 0;

		auto operator<=>(const State&) const = default;
	};
} // namespace Puzzle10B

IMPLEMENT_STD_HASH(
	Puzzle10B::State,
	value.joltageLevels[0],
	value.joltageLevels[1],
	value.joltageLevels[2],
	value.joltageLevels[3],
	value.joltageLevels[4],
	value.joltageLevels[5],
	value.joltageLevels[6],
	value.joltageLevels[7],
	value.joltageLevels[8],
	value.joltageLevels[9],
	value.nextButton);

namespace Puzzle10B
{
	uint64_t SolveMachine(const std::array<int, 10>& desiredJoltageLevels, const std::vector<std::vector<int>>& buttons)
	{
		 auto queue = std::queue<State>{};
		 auto seen = std::unordered_map<State, uint64_t>{};
		 for (auto i = 0; i < buttons.size(); ++i)
		{
			auto nextState = State{};
			nextState.nextButton = i;
			seen[nextState] = 0;
			queue.push(std::move(nextState));
		 }

		 auto currentState = State{};
		 auto presses = 0ull;
		 while (currentState.joltageLevels != desiredJoltageLevels)
		{
			auto previousState = queue.front();
			queue.pop();

			currentState = previousState;
			for (auto i : buttons[currentState.nextButton])
			{
				currentState.joltageLevels[i]++;
			}
			presses = seen[previousState] + 1;

			for (auto i = 0; i < buttons.size(); ++i)
			{
				auto nextState = currentState;
				nextState.nextButton = i;
				if (seen.contains(nextState))
				{
					continue;
				}

				bool impossible = false;
				for (auto k = 0; k < desiredJoltageLevels.size(); ++k)
				{
					if (currentState.joltageLevels[k] > desiredJoltageLevels[k])
					{
						impossible = true;
						break;
					}
				}

				if (impossible)
				{
					continue;
				}

				seen[nextState] = presses;
				queue.push(std::move(nextState));
			}
		}

		return presses;
	}

	// Does not terminate on full input. Did not optimize. Solved with Python Z3.
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		if (inputLines.size() > 3)
		{
			return "Solved in Python with z3. :( :( :(";
		}

		auto totalPresses = 0ull;
		for (const auto& line : inputLines)
		{
			auto i = 0ull;
			for (i = 1; line[i] != ']'; ++i)
			{
			}

			auto buttons = std::vector<std::vector<int>>{};
			i += 2;
			while (line[i] != '{')
			{
				auto j = i + 1;
				while (line[j] != ')')
				{
					++j;
				}

				auto buttonLights = Utilities::ExtractInt32s(std::string_view(line.data() + i, j - i));
				buttons.emplace_back(std::move(buttonLights));
				i = j + 2;
			}

			auto desiredJoltageLevels = std::array<int, 10>{};
			auto counters = ExtractInt32s(std::string_view(line.data() + i, line.size() - i));
			auto k = 0ull;
			for (auto counter : counters)
			{
				desiredJoltageLevels[k++] = counter;
			}

			auto presses = SolveMachine(desiredJoltageLevels, buttons);
			std::cout << presses << '\t' << line << '\n';
			totalPresses += presses;
		}

		return std::to_string(totalPresses);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle10B