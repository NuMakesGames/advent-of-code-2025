#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle08A
{
	struct Circuit
	{
		std::unordered_set<Vector3d<int>> junctionBoxes;

		void Connect(const Vector3d<int>& junctionBox)
		{
			junctionBoxes.insert(junctionBox);
		}

		void Connect(Circuit& other)
		{
			if (this == &other)
			{
				return;
			}

			junctionBoxes.insert_range(other.junctionBoxes);
			other.junctionBoxes.clear();
		}

		bool Contains(const Vector3d<int>& junctionBox) const
		{
			return junctionBoxes.contains(junctionBox);
		}

		size_t Size() const
		{
			return junctionBoxes.size();
		}
	};

	struct Connection
	{
		uint64_t distSquared = 0;
		Vector3d<int> left;
		Vector3d<int> right;

		auto operator<=>(const Connection&) const = default;
	};

	// 103488
	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto junctionBoxes = std::vector<Vector3d<int>>{};
		auto circuits = std::vector<Circuit>{};
		auto circuitLookup = std::unordered_map<Vector3d<int>, size_t>{};
		for (const auto& line : inputLines)
		{
			auto coords = Utilities::ExtractInt32s(line);
			auto junctionBox = Vector3d<int>{ coords[0], coords[1], coords[2] };
			junctionBoxes.emplace_back(junctionBox);
			circuitLookup[junctionBox] = circuits.size();
			circuits.emplace_back(std::unordered_set<Vector3d<int>>{ junctionBox });
		}

		auto sortedJunctionBoxPairs = std::vector<Connection>{};
		for (int i = 0; i < junctionBoxes.size() - 1; ++i)
		{
			for (int j = i + 1; j < junctionBoxes.size(); ++j)
			{
				const auto& left = junctionBoxes[i];
				const auto& right = junctionBoxes[j];

				uint64_t dx = left.x - right.x;
				uint64_t dy = left.y - right.y;
				uint64_t dz = left.z - right.z;
				uint64_t distSquared = dx * dx + dy * dy + dz * dz;
				sortedJunctionBoxPairs.emplace_back(distSquared, left, right);
				std::ranges::push_heap(sortedJunctionBoxPairs, std::greater<Connection>{});
			}
		}

		const int steps = junctionBoxes.size() == 20 ? 10 : 1000; // Sample only has 20 lines
		for (int k = 0; k < steps; ++k)
		{
			std::ranges::pop_heap(sortedJunctionBoxPairs, std::greater<Connection>{});
			const auto& connection = sortedJunctionBoxPairs.back();
			sortedJunctionBoxPairs.pop_back();

			auto iLeft = circuitLookup[connection.left];
			auto iRight = circuitLookup[connection.right];
			if (iLeft == iRight)
			{
				continue;
			}

			for (const auto& box : circuits[iRight].junctionBoxes)
			{
				circuitLookup[box] = iLeft;
			}

			circuits[iLeft].Connect(circuits[iRight]);
		}

		std::ranges::sort(
			circuits, [](const auto& leftCircuit, const auto& rightCircuit) { return leftCircuit.Size() > rightCircuit.Size(); });
		auto product = circuits[0].Size() * circuits[1].Size() * circuits[2].Size();
		return std::to_string(product);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle08A