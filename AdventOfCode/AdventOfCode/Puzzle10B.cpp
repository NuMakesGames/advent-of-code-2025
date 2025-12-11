#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"
#include "z3++.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle10B
{
	uint64_t SolveMachine(const std::vector<int>& desiredJoltageLevels, const std::vector<std::vector<int>>& buttons)
	{
		// Setup Z3 optimizer
		auto context = z3::context{};
		auto optimizer = z3::optimize{ context };

		// Create integer variables a, b, c, ... (one per button), each >= 0
		auto buttonPresses = std::vector<z3::expr>{};
		for (auto i = 0; i < buttons.size(); ++i)
		{
			auto buttonPress = context.int_const(std::string{ static_cast<char>('a' + i) }.c_str());
			buttonPresses.emplace_back(buttonPress);

			// Constraint: Button presses cannot be negative
			optimizer.add(buttonPress >= 0);
		}

		// Find buttons that contribute to each desired joltage level
		for (auto i = 0; i < desiredJoltageLevels.size(); ++i)
		{
			auto pressedButtons = std::vector<z3::expr>{};
			for (auto j = 0; j < buttons.size(); ++j)
			{
				const auto& button = buttons[j];
				if (std::ranges::find(button, i) != button.end())
				{
					pressedButtons.push_back(buttonPresses[j]);
				}
			}

			auto sum = context.int_val(0);
			for (const auto& pressedButton : pressedButtons)
			{
				sum = sum + pressedButton;
			}

			// Constraint: Combined button presses must equal desired joltage level
			optimizer.add(context.int_val(desiredJoltageLevels[i]) == sum);
		}

		// Minimize total button presses
		auto totalPresses = context.int_val(0);
		for (const auto& buttonPress : buttonPresses)
		{
			totalPresses = totalPresses + buttonPress;
		}
		optimizer.minimize(totalPresses);
		VerifyElseCrash(optimizer.check() == z3::sat);

		// Count button presses in solution
		auto result = 0ull;
		auto model = optimizer.get_model();
		for (const auto& buttonPress : buttonPresses)
		{
			result += model.eval(buttonPress, true).get_numeral_int64();
		}
		return result;
	}

	// 15883
	std::string Solve(const std::vector<std::string>& inputLines)
	{
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

			auto desiredJoltageLevels = ExtractInt32s(std::string_view(line.data() + i, line.size() - i));
			totalPresses += SolveMachine(desiredJoltageLevels, buttons);
		}

		return std::to_string(totalPresses);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle10B