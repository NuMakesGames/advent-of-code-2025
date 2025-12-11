#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle11A
{
	// 662
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto nodes = std::unordered_map<std::string, std::vector<std::string>>{};
		for (const auto& line : inputLines)
		{
			auto tokens = Utilities::SplitString(line, ": ");
			nodes[tokens[0]] = Utilities::SplitString(tokens[1], " ");
		}

		auto paths = 0ull;
		auto queue = std::queue<std::string>{};
		queue.push_range(nodes["you"]);
		while (!queue.empty())
		{
			auto node = queue.front();
			queue.pop();

			if (node == "out")
			{
				++paths;
				continue;
			}

			queue.push_range(nodes[node]);
		}

		return std::to_string(paths);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle11A