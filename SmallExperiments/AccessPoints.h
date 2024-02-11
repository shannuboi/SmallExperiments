// This is problem A from NWERC 2018, Access Points
// https://www.domjudge.org/demoweb/public/problems

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <limits>
#include <algorithm>

class Point {
public:
	Point() = default;
	Point(double x_cord, double y_cord) : x(x_cord), y(y_cord) {}
	Point operator+(const Point& rhs) const {
		return { x + rhs.x, y + rhs.y };
	}
	Point& operator+=(const Point& rhs) {
		*this = *this + rhs;
		return *this;
	}
	Point operator-(const Point& rhs) const {
		return { x - rhs.x, y - rhs.y };
	}
	Point& operator-=(const Point& rhs) {
		*this = *this - rhs;
		return *this;
	}
	Point operator*(double rhs) const {
		return { x * rhs, y * rhs };
	}
	Point& operator*=(double rhs) {
		*this = *this * rhs;
		return *this;
	}
	Point operator/(double rhs) const {
		return { x / rhs, y / rhs };
	}
	Point& operator/=(double rhs) {
		*this = *this / rhs;
		return *this;
	}
public:
	double x;
	double y;
};

class SolutionAccessPoint {
public:
	SolutionAccessPoint(std::string in_file_name, std::string out_file_name) : nTeams(-1) {
		try {
			GetInput(in_file_name);
			AssignTeams();
			OutputResult(out_file_name, GetCost());
		}
		catch (std::runtime_error err) {
			std::cout << "Runtime Error: " << err.what() << '\n';
		}
	}

private:
	void GetInput(std::string in_file_name) {
		std::ifstream input_file;
		input_file.open(in_file_name);
		if (!input_file) throw std::runtime_error("Error opening file named " + in_file_name);

		input_file >> nTeams;
		for (int i = 0; i < nTeams; i++) {
			accessPointLocs.emplace_back();
			double num;
			input_file >> num;
			accessPointLocs[i].x = num;
			input_file >> num;
			accessPointLocs[i].y = num;
		}
	}
	void AssignTeams() {
		Point curBotLeft( 0, 0 );
		for (int i = 0; i < nTeams; i++) {
			const Point& curAP = accessPointLocs[i];
			teamLocs.push_back(curAP);
			Point& curTeam = teamLocs[i];

			AdjustToBestTeamPos(i);
			ClampTeamPos(curTeam, curBotLeft);
			curBotLeft = curTeam;
		}
	}
	void AdjustToBestTeamPos(int teamNo) {
		const Point& curAP = accessPointLocs[teamNo];
		Point& curTeam = teamLocs[teamNo];

		for (int j = teamNo + 1; j < nTeams; j++) {
			Point possibleBestPos = (curAP + accessPointLocs[j]) / 2;
			curTeam.x = std::min(curTeam.x, possibleBestPos.x);
			curTeam.y = std::min(curTeam.y, possibleBestPos.y);
		}
	}
	void ClampTeamPos(Point& teamPos, const Point& botLeft) {
		teamPos.x = std::max(botLeft.x, teamPos.x);
		teamPos.y = std::max(botLeft.y, teamPos.y);
	}
	double GetCost() const {
		double cost = 0;
		for (int i = 0; i < nTeams; i++) {
			auto delta = teamLocs[i] - accessPointLocs[i];
			cost += delta.x * delta.x + delta.y * delta.y;
		}
		return cost;
	}
	void OutputResult(std::string out_file_name, double result) {
		std::ofstream output_file;
		output_file.open(out_file_name);
		if (!output_file) throw std::runtime_error("Error opening file named " + out_file_name);

		output_file << result;
	}

private:
	int nTeams;
	std::vector<Point> accessPointLocs;
	std::vector<Point> teamLocs;
};