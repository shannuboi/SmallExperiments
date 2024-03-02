#pragma once

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <vector>
#include <algorithm>

//if seed not given then arr is populated with all 1s
void GenarateMaze(int**& arr, int size, int seed = 0)
{
	// Allocating heap memory for maze
	arr = new int*[size];
	for (int i = 0; i < size; i++) arr[i] = new int[size];

	std::mt19937 rng(seed);

	// Filling with 0s and 1s
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			// if not randomised then initiallized with all 1s
			arr[y][x] = (seed != 0 ? rng() % 2 : 1);
		}
	}
}

void PrintMaze(int** arr, int size, int xStart, int yStart, int xEnd, int yEnd)
{
	const char wall = 219;
	// Top broder
	std::cout << '\t' << wall << wall;
	for (int x = 0; x < size; x++)
	{
		std::cout << wall << wall;
	}
	std::cout << wall << wall << '\n';

	// Maze
	for (int y = 0; y < size; y++)
	{
		std::cout << '\t' << wall << wall; // Left Border
		for (int x = 0; x < size; x++)
		{
			if (arr[y][x] == 1)
			{
				if (x == xStart && y == yStart) // The player
				{
					std::cout << 'P' << 'L';
				}
				else if (x == xEnd && y == yEnd) // The goal
				{
					std::cout << '[' << ']';
				}
				else
				{
					std::cout << ' ' << ' '; 
				}
			}
			else
			{
				std::cout << wall << wall;
			}
		}
		std::cout << wall << wall << '\n'; // Right border
	}

	// Bottom Border
	std::cout << '\t' << wall << wall;
	for (int x = 0; x < size; x++)
	{
		std::cout << wall << wall;
	}
	std::cout << wall << wall << '\n';
}

void DestroyMaze(int**& arr, int size)
{
	// Freeing memory used on heap
	for (int i = 0; i < size; i++) delete[] arr[i];
	delete[] arr;
}

//Each path is represented by a string
//all valid paths are stored in allPaths vector
void findPath(int x, int y, int endX, int endY, int** arr, int size,
	std::vector<std::vector<bool>> visited,
	std::vector<std::string>& allPaths, std::string curPath = "")
{
	if (x < 0 || y < 0 || x >= size || y >= size) return; // out of bound (base case)
	if (arr[y][x] == 0) return; // wall hit (base case)
	if (visited[y][x]) return; // back in a visited loc (base case)

	visited[y][x] = true;

	if (x == endX && y == endY)
	{
		// Valid path reached. Add to allPaths
		allPaths.push_back(curPath);
		return; // goal reached (base case)
	}

	findPath(x, y - 1, endX, endY, arr, size, visited, allPaths, curPath + " up"); // check up

	findPath(x + 1, y, endX, endY, arr, size, visited, allPaths, curPath + " right"); // check right

	findPath(x, y + 1, endX, endY, arr, size, visited, allPaths, curPath + " down"); // check down

	findPath(x - 1, y, endX, endY, arr, size, visited, allPaths, curPath + " left"); // check left
}

// Task 3 solution function
bool findPath(int x, int y, int endX, int endY, int** arr, int size)
{
	std::vector<std::string> allPaths;
	std::vector<std::vector<bool>> triversed;

	//initiallizing triversed vector
	for (int y = 0; y < size; y++)
	{
		std::vector<bool> row;
		for (int x = 0; x < size; x++) row.push_back(false);
		triversed.push_back(row);
	}

	findPath(x, y, endX, endY, arr, size, triversed, allPaths);

	std::vector<int> pathLengths;
	bool pathFound = false;
	for (auto path : allPaths)
	{
		// number of ' ' spaces in path str is lenght of path
		pathLengths.push_back( std::count(path.begin(), path.end(), ' ') );
		pathFound = true;
	}

	if (pathFound)
	{
		// Find shortest path index
		const auto shortest = std::min_element( pathLengths.begin(), pathLengths.end() );
		// Print path at shortest path index
		std::cout << "Shortest Path:" << allPaths.at( std::distance(pathLengths.begin(), shortest) ) 
			<< '\n';

		// Find longest path index
		const auto longest = std::max_element( pathLengths.begin(), pathLengths.end() );
		// Print path at longest path index
		std::cout << "Longest Path:" << allPaths.at( std::distance(pathLengths.begin(), longest) ) 
			<< '\n';

		std::cout << "Total Number of paths = " << allPaths.size() << '\n';
	}

	return pathFound;
}

void RunMaze(int size)
{
	// Declaring variables
	int** maze;
	int xStart;
	int yStart;
	int xEnd;
	int yEnd;

	std::random_device rd;
	const unsigned int seed = rd();
	std::mt19937 rng(seed);
	std::uniform_int_distribution<int> dist{ 0, size - 1 };

	// Initializing Variables
	GenarateMaze(maze, size, seed); // Initialize maze

	while (true) // Initialize start loc
	{
		xStart = dist(rng);
		yStart = dist(rng);
		if (maze[yStart][xStart] == 1) break;
	}
	while (true) // Initialize goal loc
	{
		xEnd = dist(rng);
		yEnd = dist(rng);
		if (maze[yEnd][xEnd] == 1) break;
	}

	std::cout << "MAZE:\n(seed = " << seed << ")\n\n";
	PrintMaze(maze, size, xStart, yStart, xEnd, yEnd);
	std::cout << "\n";

	std::cout << (findPath(xStart, yStart, xEnd, yEnd, maze, size) ? "" : "No Paths Exist") 
		<< "\n\n\n\n";

	DestroyMaze(maze, size);
}