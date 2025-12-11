#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle11B
{
	using Graph = std::unordered_map<std::string, std::vector<std::string>>;
	using Memo = std::unordered_map<std::string, uint64_t>;

	uint64_t CountPaths(const std::string& current, const std::string& target, const Graph& graph, Memo& memo)
	{
		if (memo.contains(current))
		{
			return memo[current];
		}

		if (current == target)
		{
			memo[current] = 1;
			return memo[current];
		}

		auto result = 0ull;
		auto itNext = graph.find(current);
		if (itNext != graph.end())
		{
			for (const auto& next : itNext->second)
			{
				result += CountPaths(next, target, graph, memo);
			}
		}

		memo[current] = result;
		return result;
	}

	// 429399933071120
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto nodes = std::unordered_set<std::string>{};
		auto graph = Graph{};
		for (const auto& line : inputLines)
		{
			auto tokens = Utilities::SplitString(line, ": ");
			auto destinations = Utilities::SplitString(tokens[1], " ");
			graph[tokens[0]] = destinations;
			nodes.insert(tokens[0]);
			nodes.insert_range(destinations);
		}

		// Wrote out graphviz and visualized to confirm DAG
		auto svrToFftMemo = Memo{};
		auto svrToFftPaths = CountPaths("svr", "fft", graph, svrToFftMemo);

		auto fftToDacMemo = Memo{};
		auto fftToDacPaths = CountPaths("fft", "dac", graph, fftToDacMemo);

		auto dacToOutMemo = Memo{};
		auto dacToOutPaths = CountPaths("dac", "out", graph, dacToOutMemo);

		return std::to_string(svrToFftPaths * fftToDacPaths * dacToOutPaths);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle11B