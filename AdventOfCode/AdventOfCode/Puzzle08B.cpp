#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace Utilities;
using namespace nu::asserts;
using namespace nu::console;
using namespace nu::console::vt;

namespace Puzzle08B
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

		auto result = 0ull;
		for (const auto& connection : sortedJunctionBoxPairs)
		{
			auto& leftCircuit =
				*std::ranges::find_if(circuits, [&connection](const auto& circuit) { return circuit.Contains(connection.left); });
			auto& rightCircuit =
				*std::ranges::find_if(circuits, [&connection](const auto& circuit) { return circuit.Contains(connection.right); });
			leftCircuit.Connect(rightCircuit);

			std::erase_if(circuits, [](const Circuit& circuit) { return circuit.Size() == 0; });
			if (circuits.size() == 1)
			{
				result = static_cast<uint64_t>(connection.left.x) * connection.right.x;
				break;
			}
		}

		return std::to_string(result);
	}

	std::string Visualize(const std::vector<std::string>& inputLines)
	{
		return Solve(inputLines);
	}
} // namespace Puzzle08B