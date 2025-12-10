#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle10A
{
	struct State
	{
		std::bitset<10> lights = 0;
		size_t nextButton = 0;

		auto operator<=>(const State&) const = default;
	};
} // namespace Puzzle10A

IMPLEMENT_STD_HASH(Puzzle10A::State, value.lights, value.nextButton);

namespace Puzzle10A
{
	// 425
	uint64_t SolveMachine(const std::bitset<10>& desiredLights, const std::vector<std::vector<int>>& buttons)
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
		while (currentState.lights != desiredLights)
		{
			auto previousState = queue.front();
			queue.pop();

			currentState = previousState;
			for (auto i : buttons[currentState.nextButton])
			{
				currentState.lights.flip(i);
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

				seen[nextState] = presses;
				queue.push(std::move(nextState));
			}
		}

		return presses;
	}

	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto totalPresses = 0ull;
		for (const auto& line : inputLines)
		{
			auto desiredLights = std::bitset<10>{};
			auto i = 0ull;
			for (i = 1; line[i] != ']'; ++i)
			{
				if (line[i] == '#')
				{
					desiredLights.set(i - 1);
				}
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

			auto presses = SolveMachine(desiredLights, buttons);
			totalPresses += presses;
		}

		return std::to_string(totalPresses);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle10A