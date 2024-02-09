#include <iostream>
#include "NumberOfIslandsProblem.h"

int main()
{
	NumberOfIslandsProblem::Input inp = {
		{1,1,0,0,0},
		{0,1,0,0,0},
		{1,0,1,1,1},
		{0,0,0,0,0},
		{1,0,1,0,0}
	};

	NumberOfIslandsProblem problem;
	std::cout << problem.GetNumIslands(inp);
}