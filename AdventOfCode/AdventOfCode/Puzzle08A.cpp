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

	std::string Solve(const std::vector<std::string>& inputLines)
	{
		auto junctionBoxes = std::vector<Vector3d<int>>{};
		auto circuits = std::vector<Circuit>{};
		for (const auto& line : inputLines)
		{
			auto coords = Utilities::ExtractInt32s(line);
			auto junctionBox = Vector3d<int>{ coords[0], coords[1], coords[2] };
			junctionBoxes.emplace_back(junctionBox);
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
			}
		}
		std::ranges::sort(sortedJunctionBoxPairs);

		const int steps = junctionBoxes.size() == 20 ? 10 : 1000; // Sample only has 20 lines
		for (int k = 0; k < steps; ++k)
		{
			auto& connection = sortedJunctionBoxPairs[k];

			auto& leftCircuit = *std::ranges::find_if(
				circuits, [&connection](const auto& circuit) { return circuit.Contains(connection.left); });
			auto& rightCircuit = *std::ranges::find_if(
				circuits, [&connection](const auto& circuit) { return circuit.Contains(connection.right); });
			leftCircuit.Connect(rightCircuit);
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