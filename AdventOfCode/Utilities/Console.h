#pragma once

#include "Grid2d.h"
#include "NuEngine/ConsoleRenderer.h"
#include "NuEngine/VirtualTerminalSequences.h"

namespace Utilities
{
	// Draws a grid at the provided position
	bool DrawGrid(
		class nu::console::ConsoleRenderer& renderer,
		int x,
		int y,
		const Grid2d<char>& grid,
		std::string_view foregroundColor = nu::console::vt::color::ForegroundWhite,
		std::string_view backgroundColor = nu::console::vt::color::BackgroundBlack);

	// Draws a grid at the provided position
	template<typename T>
	bool DrawGrid(
		class nu::console::ConsoleRenderer& renderer,
		T&& position,
		const Grid2d<char>& grid,
		std::string_view foregroundColor = nu::console::vt::color::ForegroundWhite,
		std::string_view backgroundColor = nu::console::vt::color::BackgroundBlack)
	{
		return DrawGrid(position.x, position.y, grid, foregroundColor, backgroundColor);
	}

	// Draws a grid at the provided positions
	template<std::ranges::input_range R>
	bool DrawGrid(
		class nu::console::ConsoleRenderer& renderer,
		R&& range,
		const Grid2d<char>& grid,
		std::string_view foregroundColor = nu::console::vt::color::ForegroundWhite,
		std::string_view backgroundColor = nu::console::vt::color::BackgroundBlack)
	{
		bool result = true;
		for (const auto& position : range)
		{
			result = result && DrawGrid(position, grid, foregroundColor, backgroundColor);
		}
		return result;
	}
} // namespace Utilities