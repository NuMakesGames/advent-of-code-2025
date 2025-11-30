// AdventOfCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "../Utilities/Utilities.h"
#include "PuzzleSolvers.h"

#define NOMINMAX
#include <Windows.h>

using namespace std::chrono_literals;
using namespace Utilities;
using namespace nu::console;
using namespace nu::console::vt;

const std::unordered_set<std::string> validArgs = { "--sampleInput", "--fullInput", "--visualize", "--partA",    "--partB",    "--puzzle01",
	                                                "--puzzle02",    "--puzzle03",  "--puzzle04",  "--puzzle05", "--puzzle06", "--puzzle07",
	                                                "--puzzle08",    "--puzzle09",  "--puzzle10",  "--puzzle11", "--puzzle12" };

struct SolverFunctions
{
	std::function<std::string(const std::vector<std::string>&)> solvePartA;
	std::function<std::string(const std::vector<std::string>&)> solvePartB;
	std::function<std::string(const std::vector<std::string>&)> visualizePartA;
	std::function<std::string(const std::vector<std::string>&)> visualizePartB;
};

const std::array<SolverFunctions, 12> solvers = {
	SolverFunctions{ Puzzle01A::Solve, Puzzle01B::Solve, Puzzle01A::Visualize, Puzzle01B::Visualize },
	SolverFunctions{ Puzzle02A::Solve, Puzzle02B::Solve, Puzzle02A::Visualize, Puzzle02B::Visualize },
	SolverFunctions{ Puzzle03A::Solve, Puzzle03B::Solve, Puzzle03A::Visualize, Puzzle03B::Visualize },
	SolverFunctions{ Puzzle04A::Solve, Puzzle04B::Solve, Puzzle04A::Visualize, Puzzle04B::Visualize },
	SolverFunctions{ Puzzle05A::Solve, Puzzle05B::Solve, Puzzle05A::Visualize, Puzzle05B::Visualize },
	SolverFunctions{ Puzzle06A::Solve, Puzzle06B::Solve, Puzzle06A::Visualize, Puzzle06B::Visualize },
	SolverFunctions{ Puzzle07A::Solve, Puzzle07B::Solve, Puzzle07A::Visualize, Puzzle07B::Visualize },
	SolverFunctions{ Puzzle08A::Solve, Puzzle08B::Solve, Puzzle08A::Visualize, Puzzle08B::Visualize },
	SolverFunctions{ Puzzle09A::Solve, Puzzle09B::Solve, Puzzle09A::Visualize, Puzzle09B::Visualize },
	SolverFunctions{ Puzzle10A::Solve, Puzzle10B::Solve, Puzzle10A::Visualize, Puzzle10B::Visualize },
	SolverFunctions{ Puzzle11A::Solve, Puzzle11B::Solve, Puzzle11A::Visualize, Puzzle11B::Visualize },
	SolverFunctions{ Puzzle12A::Solve, Puzzle12B::Solve, Puzzle12A::Visualize, Puzzle12B::Visualize }
};

const std::array<std::vector<std::filesystem::path>, 12> puzzleInputPaths = {
	std::vector<std::filesystem::path>{ "Puzzle01.input" }, std::vector<std::filesystem::path>{ "Puzzle02.input" },
	std::vector<std::filesystem::path>{ "Puzzle03.input" }, std::vector<std::filesystem::path>{ "Puzzle04.input" },
	std::vector<std::filesystem::path>{ "Puzzle05.input" }, std::vector<std::filesystem::path>{ "Puzzle06.input" },
	std::vector<std::filesystem::path>{ "Puzzle07.input" }, std::vector<std::filesystem::path>{ "Puzzle08.input" },
	std::vector<std::filesystem::path>{ "Puzzle09.input" }, std::vector<std::filesystem::path>{ "Puzzle10.input" },
	std::vector<std::filesystem::path>{ "Puzzle11.input" }, std::vector<std::filesystem::path>{ "Puzzle12.input" }
};

const std::array<std::vector<std::vector<std::filesystem::path>>, 12> puzzleSamplePaths = { std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle01SampleA.input" },
																								{ "Puzzle01SampleA.input" },
																							},
	                                                                                        std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle02SampleA.input" },
																								{ "Puzzle02SampleA.input" },
																							},
	                                                                                        std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle03SampleA.input" },
																								{ "Puzzle03SampleA.input" },
																							},
	                                                                                        std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle04SampleA.input" },
																								{ "Puzzle04SampleA.input" },
																							},
	                                                                                        std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle05SampleA.input" },
																								{ "Puzzle05SampleA.input" },
																							},
	                                                                                        std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle06SampleA.input" },
																								{ "Puzzle06SampleA.input" },
																							},
	                                                                                        std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle07SampleA.input" },
																								{ "Puzzle07SampleA.input" },
																							},
	                                                                                        std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle08SampleA.input" },
																								{ "Puzzle08SampleA.input" },
																							},
	                                                                                        std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle09SampleA.input" },
																								{ "Puzzle09SampleA.input" },
																							},
	                                                                                        std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle10SampleA.input" },
																								{ "Puzzle10SampleA.input" },
																							},
	                                                                                        std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle11SampleA.input" },
																								{ "Puzzle11SampleA.input" },
																							},
	                                                                                        std::vector<std::vector<std::filesystem::path>>{
																								{ "Puzzle12SampleA.input" },
																								{ "Puzzle12SampleA.input" },
																							} };

struct Args
{
	bool useSampleInput = false;
	bool useFullInput = false;
	bool shouldVisualize = false;
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
				else if (arg == "--visualize")
				{
					result.shouldVisualize = true;
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
	::timeBeginPeriod(1); // Request 1 ms timer resolution for more accurate measurements (Windows default is 15.6 ms).

	Args args = ReadArgs(argc, argv);
	if (args.puzzlesToRun.empty())
	{
		std::cout << color::ForegroundBrightRed
				  << "\nNo puzzles specified for execution. Pass desired puzzles as command-line arguments. Sample usage:\n";
		std::cout << color::ForegroundBrightWhite << "  AdventOfCode.exe ";
		std::cout << color::ForegroundBrightGreen << "--puzzle04\n";
		std::cout << color::ForegroundBrightWhite << "  AdventOfCode.exe ";
		std::cout << color::ForegroundBrightGreen << "--visualize --puzzle01 --puzzle02\n";
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

			const auto& solverFunctions = solvers[puzzleId - 1];
			const auto& solver = args.shouldVisualize ? (i == 0 ? solverFunctions.visualizePartA : solverFunctions.visualizePartB)
			                                          : (i == 0 ? solverFunctions.solvePartA : solverFunctions.solvePartB);
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
				auto inputLines = ReadAllLinesInFile(fullInputPath);

				auto start = std::chrono::high_resolution_clock::now();
				auto result = solver(inputLines);
				auto stop = std::chrono::high_resolution_clock::now();
				totalDurationMs += std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

				// Printing to cout is a substantial time cost on fast problems, so solvers return the solution as a string.
				std::cout << color::ForegroundRGB(0xff, 0xff, 0x66) << result;

				{
					std::cout << color::ForegroundBrightWhite << "\nSolver executed in ";
					auto durationUs = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
					if (durationUs > 1000us)
					{
						auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
						std::cout << color::ForegroundBrightBlue << durationMs.count() << "." << durationUs.count() % 1000 << " ms";
					}
					else
					{
						std::cout << color::ForegroundBrightBlue << durationUs.count() << " us";
					}
					std::cout << color::ForegroundBrightWhite << ".\n";
				}
			}
		}
	}

	if (args.puzzlesToRun.size() > 1)
	{
		std::cout << color::ForegroundBrightWhite << "\nAll solvers executed in ";
		std::cout << color::ForegroundBrightBlue << totalDurationMs.count() << " ms";
		std::cout << color::ForegroundBrightWhite << ".\n";
	}

	::timeEndPeriod(1); // Restore default timer resolution.
	nu::console::RestoreConsoleState(consoleState, false /*shouldRestorePosition*/);
}