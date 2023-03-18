// this is problem 1 from chilitomatonoodle's coding challenges series

#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>

class SolutionPyramid {
public:
	SolutionPyramid(std::string in_file_name, std::string out_file_name) {
		try {
			GetInput(in_file_name);
			int sum = CalcSum();
		}
		catch (std::runtime_error err) {
			std::cout << "Runtime Error: " << err.what() << '\n';
		}
	}
	void GetInput(std::string in_file_name) {
		std::ifstream input_file;
		input_file.open(in_file_name);
		if (!input_file) throw std::runtime_error("File " + in_file_name + " not found");

		std::string line;
		int line_no = 1;
		while (std::getline(input_file, line)) {
			std::vector<int> row;
			std::stringstream linestream(line);
			for (int i = 0; i < line_no; i++) {
				int temp = 0;
				linestream >> temp;
				row.emplace_back(temp);
			}
			pyramid.push_back(std::move(row));
			line_no++;
		}
	}
	int CalcSum() {
		for (int line = pyramid.size() - 2; line >= 0; line--)
			for (int i = 0; i < pyramid[line].size(); i++)
				pyramid[line][i] += std::max(pyramid[line + 1][i], pyramid[line + 1][i + 1]);
		std::cout << pyramid[0][0] << '\n';
		return pyramid[0][0];
	}
private:
	std::vector<std::vector<int>> pyramid;
};