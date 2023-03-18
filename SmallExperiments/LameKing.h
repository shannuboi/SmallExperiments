// This is problem 1804 A from codeforces website, Lame King
// https://codeforces.com/problemset/problem/1804/A

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>

class Coord {
public:
	Coord() = default;
	Coord(int x_cord, int y_cord) : col(x_cord), row(y_cord) {}
public:
	int col;
	int row;
};

class SolutionLameKing {
public:
	SolutionLameKing(std::string in_file_name) {
		try {
			GetInput(in_file_name);
			DoTests();
		}
		catch (std::runtime_error err) {
			std::cout << "Runtime Error: " << err.what() << '\n';
		}
	}
	void GetInput(std::string in_file_name) {
		std::ifstream input_file;
		input_file.open(in_file_name);
		if (!input_file) throw std::runtime_error("File " + in_file_name + " not found");

		int nTests;
		input_file >> nTests;
		for (int i = 0; i < nTests; i++) {
			tests.emplace_back();
			int num;
			input_file >> num;
			tests[i].col = num;
			input_file >> num;
			tests[i].row = num;
		}
	}
	void DoTests() {
		for (auto coord : tests) {
			int x = abs(coord.col);
			int y = abs(coord.row);
			if (x > y) 
				std::swap(x, y);
			if (y == x)
				std::cout << 2 * y << '\n';
			else
				std::cout << 2 * y - 1 << '\n';
		}
	}
private:
	std::vector<Coord> tests;
};
