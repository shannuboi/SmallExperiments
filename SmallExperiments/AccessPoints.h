// This is problem A from NWERC 2018

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>

class Point {
public:
	Point() = default;
	Point(double x_cord, double y_cord) : x(x_cord), y(y_cord) {}
public:
	double x;
	double y;
};

class Solution {
public:
	Solution(std::string in_file_name, std::string out_file_name) : nTeams(-1) {
		try {
			GetInput(in_file_name);
			double total_cost = AssignTeams();
			OutputResult(out_file_name, total_cost);
		}
		catch (std::runtime_error err) {
			std::cout << "Runtime Error: " << err.what() << '\n';
		}
	}
	void GetInput(std::string in_file_name) {
		std::ifstream input_file;
		input_file.open(in_file_name);
		if (!input_file) throw std::runtime_error("File " + in_file_name + " not found");
		
		input_file >> nTeams;
		for (int i = 0; i < nTeams; i++) {
			accessPoints.emplace_back();
			double num;
			input_file >> num;
			accessPoints[i].x = num;
			input_file >> num;
			accessPoints[i].y = num;
		}
	}
	double AssignTeams() {
		return 0.0;
	}
	void OutputResult(std::string out_file_name, double result) {
		std::ofstream output_file;
		output_file.open(out_file_name);
		if (!output_file) throw std::runtime_error("File " + out_file_name + " not found");

		output_file << result;
	}
private:
	int nTeams;
	std::vector<Point> accessPoints;
};