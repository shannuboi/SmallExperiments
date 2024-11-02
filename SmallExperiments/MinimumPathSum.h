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

class Solution {
public:
    int minPathSum(std::vector<std::vector<int>>& grid) {
        std::vector<int> row(grid[0].size(), -1);
        std::vector<std::vector<int>> savedValues(grid.size(), std::move(row));

        return getMinPathSum(grid, savedValues, 0, 0);
    }
private:
    static constexpr int INF = std::numeric_limits<int>::max();
    int getMinPathSum(
        const std::vector<std::vector<int>>& grid,
        std::vector<std::vector<int>>& savedValues,
        int y, int x) {

        if (y >= grid.size()) return INF;
        if (x >= grid[0].size()) return INF;

        if (savedValues[y][x] != -1) return savedValues[y][x];

        int left = getMinPathSum(grid, savedValues, y, x + 1);
        int down = getMinPathSum(grid, savedValues, y + 1, x);

        int pathVal = std::min(left, down);
        if (pathVal == INF)
            pathVal = grid[y][x];
        else
            pathVal += grid[y][x];

        savedValues[y][x] = pathVal;
        return pathVal;
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

getMinPathSum(grid, saved_values, x, y)
    if y == grid.height
        return inf
    if x == grid.width
        return inf

    check and return if x,y in saved values

    down = getMinPathSum(grid, saved_values, x, y+1)
    left = getMinPathSum(grid, saved_values, x+1, y)
    
    path = min(down,left)
    if path == inf
        path = grid[y][x]
    else
        path += grid[y][x]

    values[y][x] = path
    return path


*/