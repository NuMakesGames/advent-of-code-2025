// AdventOfCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

using namespace std::chrono_literals;
using namespace Utilities;
using namespace nu::console;
using namespace nu::console::vt;

const std::unordered_set<std::string> validArgs = { "--sampleInput", "--fullInput", "--render",   "--partA",    "--partB",    "--puzzle01",
	                                                "--puzzle02",    "--puzzle03",  "--puzzle04", "--puzzle05", "--puzzle06", "--puzzle07",
	                                                "--puzzle08",    "--puzzle09",  "--puzzle10", "--puzzle11", "--puzzle12" };

const std::vector<std::function<void(const std::filesystem::path&, bool)>> partASolvers = {
	Puzzle01A::PrintSolution, Puzzle02A::PrintSolution, Puzzle03A::PrintSolution, Puzzle04A::PrintSolution,
	Puzzle05A::PrintSolution, Puzzle06A::PrintSolution, Puzzle07A::PrintSolution, Puzzle08A::PrintSolution,
	Puzzle09A::PrintSolution, Puzzle10A::PrintSolution, Puzzle11A::PrintSolution, Puzzle12A::PrintSolution
};

const std::vector<std::function<void(const std::filesystem::path&, bool)>> partBSolvers = {
	Puzzle01B::PrintSolution, Puzzle02B::PrintSolution, Puzzle03B::PrintSolution, Puzzle04B::PrintSolution,
	Puzzle05B::PrintSolution, Puzzle06B::PrintSolution, Puzzle07B::PrintSolution, Puzzle08B::PrintSolution,
	Puzzle09B::PrintSolution, Puzzle10B::PrintSolution, Puzzle11B::PrintSolution, Puzzle12B::PrintSolution
};

const std::vector<std::vector<std::filesystem::path>> puzzleInputPaths = {
	{ "Puzzle01.input" }, { "Puzzle02.input" }, { "Puzzle03.input" }, { "Puzzle04.input" }, { "Puzzle05.input" },
	{ "Puzzle06.input" }, { "Puzzle07.input" }, { "Puzzle08.input" }, { "Puzzle09.input" }, { "Puzzle10.input" },
	{ "Puzzle11.input" }, { "Puzzle12.input" }, { "Puzzle13.input" }, { "Puzzle14.input" }, { "Puzzle15.input" },
	{ "Puzzle16.input" }, { "Puzzle17.input" }, { "Puzzle18.input" }, { "Puzzle19.input" }, { "Puzzle20.input" },
	{ "Puzzle21.input" }, { "Puzzle22.input" }, { "Puzzle23.input" }, { "Puzzle24.input" }, { "Puzzle25.input" },
};

const std::vector<std::vector<std::vector<std::filesystem::path>>> puzzleSamplePaths = { {
																							 { "Puzzle01SampleA.input" },
																							 { "Puzzle01SampleA.input" },
																						 },
	                                                                                     {
																							 { "Puzzle02SampleA.input" },
																							 { "Puzzle02SampleA.input" },
																						 },
	                                                                                     {
																							 { "Puzzle03SampleA.input" },
																							 { "Puzzle03SampleA.input" },
																						 },
	                                                                                     {
																							 { "Puzzle04SampleA.input" },
																							 { "Puzzle04SampleA.input" },
																						 },
	                                                                                     {
																							 { "Puzzle05SampleA.input" },
																							 { "Puzzle05SampleA.input" },
																						 },
	                                                                                     {
																							 { "Puzzle06SampleA.input" },
																							 { "Puzzle06SampleA.input" },
																						 },
	                                                                                     {
																							 { "Puzzle07SampleA.input" },
																							 { "Puzzle07SampleA.input" },
																						 },
	                                                                                     {
																							 { "Puzzle08SampleA.input" },
																							 { "Puzzle08SampleA.input" },
																						 },
	                                                                                     {
																							 { "Puzzle09SampleA.input" },
																							 { "Puzzle09SampleA.input" },
																						 },
	                                                                                     {
																							 { "Puzzle10SampleA.input" },
																							 { "Puzzle10SampleA.input" },
																						 },
	                                                                                     {
																							 { "Puzzle11SampleA.input" },
																							 { "Puzzle11SampleA.input" },
																						 },
	                                                                                     {
																							 { "Puzzle12SampleA.input" },
																							 { "Puzzle12SampleA.input" },
																						 } };

struct Args
{
	bool useSampleInput = false;
	bool useFullInput = false;
	bool shouldRender = false;
	bool runPartA = false;
	bool runPartB = false;
	std::vector<int> puzzlesToRun;
};

Args ReadArgs(int argc, char* argv[])
{
	std::cout << color::ForegroundBrightGreen << "A";
	std::cout << color::ForegroundBrightRed << 'd';
	std::cout << color::ForegroundBrightGreen << 'v';
	std::cout << color::ForegroundBrightRed << 'e';
	std::cout << color::ForegroundBrightGreen << 'n';
	std::cout << color::ForegroundBrightRed << 't';
	std::cout << color::ForegroundBrightGreen << " O";
	std::cout << color::ForegroundBrightRed << 'f';
	std::cout << color::ForegroundBrightGreen << " C";
	std::cout << color::ForegroundBrightRed << 'o';
	std::cout << color::ForegroundBrightGreen << 'd';
	std::cout << color::ForegroundBrightRed << 'e';
	std::cout << color::ForegroundBrightGreen << " 2";
	std::cout << color::ForegroundBrightRed << '0';
	std::cout << color::ForegroundBrightGreen << '2';
	std::cout << color::ForegroundBrightRed << "5\n";

	Args result;
	if (argc > 1)
	{
		std::cout << color::ForegroundBrightWhite << "Command line arguments:\n";
		auto color = color::ForegroundBrightGreen;
		for (int i = 1; i < argc; ++i)
		{
			std::string arg = argv[i];
			if (validArgs.contains(arg))
			{
				if (arg == "--sampleInput")
				{
					result.useSampleInput = true;
				}
				else if (arg == "--fullInput")
				{
					result.useFullInput = true;
				}
				else if (arg == "--render")
				{
					result.shouldRender = true;
				}
				else if (arg == "--partA")
				{
					result.runPartA = true;
				}
				else if (arg == "--partB")
				{
					result.runPartB = true;
				}
				else
				{
					result.puzzlesToRun.push_back(std::stoi(arg.substr(arg.size() - 2)));
				}
			}
			else
			{
				color = color::ForegroundBrightRed;
			}

			std::cout << color << "    " << argv[i] << "\n";
		}
	}

	if (!result.runPartA && !result.runPartB)
	{
		result.runPartA = true;
		result.runPartB = true;
	}

	if (!result.useSampleInput && !result.useFullInput)
	{
		result.useSampleInput = true;
		result.useFullInput = true;
	}

	std::ranges::sort(result.puzzlesToRun);
	return result;
}

int main(int argc, char* argv[])
{
	auto consoleState = CacheConsoleState();
	nu::console::EnableVirtualTerminalProcessing();

	Args args = ReadArgs(argc, argv);
	if (args.puzzlesToRun.empty())
	{
		std::cout << color::ForegroundBrightRed
				  << "\nNo puzzles specified for execution. Pass desired puzzles as command-line arguments. Sample usage:\n";
		std::cout << color::ForegroundBrightWhite << "  AdventOfCode.exe ";
		std::cout << color::ForegroundBrightGreen << "--puzzle04\n";
		std::cout << color::ForegroundBrightWhite << "  AdventOfCode.exe ";
		std::cout << color::ForegroundBrightGreen << "--render --puzzle01 --puzzle02\n";
		std::cout << color::ForegroundBrightWhite << "  AdventOfCode.exe ";
		std::cout << color::ForegroundBrightGreen << "--partB --fullInput --puzzle02\n";
		std::cout << color::ForegroundBrightWhite << "  AdventOfCode.exe ";
		std::cout << color::ForegroundBrightGreen << "--partA --sampleInput --puzzle03\n";
	}

	auto totalDurationMs = 0ms;
	for (int puzzleId : args.puzzlesToRun)
	{
		for (auto i = 0; i < 2; ++i)
		{
			if (i == 0 && !args.runPartA)
			{
				continue;
			}

			if (i == 1 && !args.runPartB)
			{
				continue;
			}

			{
				std::cout << color::ForegroundBrightWhite << "\nRunning puzzle ";
				std::cout << color::ForegroundBrightCyan << puzzleId;
				std::cout << color::ForegroundBrightWhite << ", part ";
				std::cout << (i == 0 ? color::ForegroundBrightGreen : color::ForegroundBrightRed);
				std::cout << (i == 0 ? 'A' : 'B');
				std::cout << color::ForegroundBrightWhite << ":\n";
			}

			std::vector<std::filesystem::path> inputPaths;
			if (args.useSampleInput)
			{
				inputPaths.append_range(puzzleSamplePaths[puzzleId - 1][i]);
			}
			if (args.useFullInput)
			{
				inputPaths.append_range(puzzleInputPaths[puzzleId - 1]);
			}

			const auto solver = i == 0 ? partASolvers[puzzleId - 1] : partBSolvers[puzzleId - 1];
			for (const auto& inputPath : inputPaths)
			{
				{
					std::cout << color::ForegroundWhite << "Using input file ";
					std::cout << color::ForegroundBrightCyan << inputPath;
					std::cout << color::ForegroundWhite << ":\n";
				}

				// Fully qualify the path to the input files, which have been copied next to the executable.
				static const std::filesystem::path executablePath = argv[0];
				std::filesystem::path fullInputPath = executablePath.parent_path() / inputPath;

				auto start = std::chrono::high_resolution_clock::now();
				solver(fullInputPath, args.shouldRender);
				auto stop = std::chrono::high_resolution_clock::now();
				totalDurationMs += std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

				{
					std::cout << color::ForegroundBrightWhite << "\nSolver executed in ";
					auto durationUs = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
					if (durationUs > 1000us)
					{
						auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
						std::cout << color::ForegroundBrightYellow << durationMs.count() << "." << durationUs.count() % 1000 << " ms";
					}
					else
					{
						std::cout << color::ForegroundBrightYellow << durationUs.count() << " us";
					}
					std::cout << color::ForegroundBrightWhite << ".\n";
				}
			}
		}
	}

	if (args.puzzlesToRun.size() > 1)
	{
		std::cout << color::ForegroundBrightWhite << "\nAll solvers executed in ";
		std::cout << color::ForegroundBrightYellow << totalDurationMs.count() << " ms";
		std::cout << color::ForegroundBrightWhite << ".\n";
	}

	nu::console::RestoreConsoleState(consoleState, false /*shouldRestorePosition*/);
}