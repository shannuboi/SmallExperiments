#pragma once

/*
https://leetcode.com/problems/minimum-path-sum/description/

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom down, which minimizes the sum of all numbers along its path.
Note: You can only move either down or down at any point in time.

Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

Input: grid = [[1,2,3],[4,5,6]]
Output: 12

Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 200
0 <= grid[i][j] <= 200
*/

#include <vector>

using namespace std;

class Solution {
public:
	static constexpr int INF = numeric_limits<int>::max();
	int minPathSum(vector<vector<int>>& grid) {
		int h = grid.size(); int w = grid[0].size();
		vector<int> PS(w+1, INF); PS[w-1] = grid[h-1][w-1];
		for (int y = h-1; y >= 0; y--)
			for (int x = (y==h-1 ? w-2 : w-1); x >= 0; x--)
				PS[x] = grid[y][x] + min(PS[x+1], PS[x]);
		return PS[0];
	}
};

/*
Need to find path by going down or left each turn
	value of path is sum of ints along path
At any location its best value is 
	its own int 
	plus the shorter of the best values of 
		down and 
		left cell
Seems like recursion
	But on deeper thought some recursive cases reappear...
		DP?
		Yes

Ez solution use memoization (top down)
	save a capy of the original grid which will hold all path values
	When a path value is found add save it to this copy
	Saves need for recalculation

getMinPathSum(x, y)
	if y == grid.height
		return inf
	if x == grid.width
		return inf

	check and return if x,y is saved

	down = getMinPathSum(grid, saved_values, x, y+1)
	left = getMinPathSum(grid, saved_values, x+1, y)
	
	path = min(down,left)
	if path == inf
		path = grid[y][x]
	else
		path += grid[y][x]

	save that x,y returns path
	return path


Now im kinda curious about what the bottom up approach looks like... hmmm
BOUNDS:
	x: [0, grid.width]
	y: [0, grid.height]

initial therefor statespace
[[-1 (width)] (height)]

ORDER:
	x,y:
		down -> x, y+1
			- x dosnt change
			- y+1 before y
			- big b4 small
			- loop from grid.height to 0
		left -> x+1, y
			- y dosnt change
			- x+1 b4 x
			- big b4 small
			- loop from grid.width to 0


*/