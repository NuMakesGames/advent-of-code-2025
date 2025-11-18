#include "pch.h"

#include "Console.h"

namespace Utilities
{
	bool DrawGrid(
		nu::console::ConsoleRenderer& renderer,
		int x,
		int y,
		const Grid2d<char>& grid,
		std::string_view foregroundColor,
		std::string_view backgroundColor)
	{
		bool result = true;
		for (int j = 0; j < grid.Height(); ++j)
		{
			for (int i = 0; i < grid.Width(); ++i)
			{
				result = result && renderer.DrawChar(x + i, y + j, grid.at(i, j), foregroundColor, backgroundColor);
			}
		}
		return result;
	}
} // namespace Utilities