#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <assert.h>
#include <algorithm>

class NumberOfIslandsProblem
{
public:
	typedef std::vector<std::vector<int>> Input;
	typedef std::vector<std::vector<bool>> Visited;
public:
	int GetNumIslands(const Input& input) {
		matrix = input;
		size = (int)matrix.size();

		Visited visited;
		visited.resize(size, std::vector<bool>(size, false));
		int count = 0;
		for (int y = 0; y < size; y++) {
			for (int x = 0; x < size; x++) {
				if (!visited[y][x] && matrix[y][x] == ISLAND) {
					count++;
					DFS(visited, y, x);
				}
			}
		}
		return count;
	}
private:
	void DFS(Visited& visited, int cur_y, int cur_x) {
		visited[cur_y][cur_x] = true;

		const int yStart = std::max(cur_y - 1, 0);
		const int yEnd = std::min(cur_y + 2, size);
		const int xStart = std::max(cur_x - 1, 0);
		const int xEnd = std::min(cur_x + 2, size);
		for (int y = yStart; y < yEnd; y++) {
			for (int x = xStart; x < xEnd; x++) {
				if (!visited[y][x] && matrix[y][x] == ISLAND) {
					DFS(visited, y, x);
				}
			}
		}
	}
private:
	Input matrix;
	int size;
	static constexpr int ISLAND = 1;
};