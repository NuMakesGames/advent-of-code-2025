#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle11B
{
	using Path = std::vector<std::string>;
	using Paths = std::vector<Path>;
	using Graph = std::unordered_map<std::string, std::vector<std::string>>;
	using Memo = std::unordered_map<std::string, Paths>;

	Paths DepthFirstSearchAllPaths(const std::string& current, const std::string& target, const Graph& graph, std::unordered_map<std::string, Paths>& memo)
	{
		if (memo.contains(current))
		{
			return memo[current];
		}

		auto result = Paths{};
		if (current == target)
		{
			auto path = Path{};
			path.push_back(target);
			result.push_back(path);
			memo[current] = result;
			return result;
		}

		auto itNext = graph.find(current);
		if (itNext != graph.end())
		{
			for (const auto& next : itNext->second)
			{
				auto paths = DepthFirstSearchAllPaths(next, target, graph, memo);
				for (const auto& path : paths)
				{
					auto newPath = Path{};
					newPath.push_back(current);
					newPath.insert_range(newPath.end(), path);
					result.push_back(newPath);
				}
			}
		}

		memo[current] = result;
		return result;
	}


	// 114672848 too low
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
		auto svrToFftPaths = DepthFirstSearchAllPaths("svr", "fft", graph, svrToFftMemo);

		auto fftToDacMemo = Memo{};
		auto fftToDacPaths = DepthFirstSearchAllPaths("fft", "dac", graph, fftToDacMemo);

		auto dacToOutMemo = Memo{};
		auto dacToOutPaths = DepthFirstSearchAllPaths("dac", "out", graph, dacToOutMemo);

		return std::to_string(svrToFftPaths.size() * fftToDacPaths.size() * dacToOutPaths.size());
	}


	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle11B