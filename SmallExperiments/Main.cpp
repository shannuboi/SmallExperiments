#include <iostream>
#include "MinimumPathSum.h"

int main() {
	Solution s;
	std::vector<std::vector<int>> grid = { {1, 2, 3}, {4, 5, 6} };
    std::cout << s.minPathSum(grid);
}