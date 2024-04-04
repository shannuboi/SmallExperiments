#pragma once

#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <ranges>
#include <iostream>
#include <assert.h>

class BullyAlgSimulator {
private:
	class Event {
	public:
		enum class Type {
			Election, Ok, Coordinator
		};
	public:
		Type type;
		int sendingProc;
		int recievingProc;
	};
	class Process {
	public:
		void SendElectionMsg(const Process& recipient) {

		}
		void SendOkMsg(const Process& recipient) {

		}
		void SendCoordinatorMsg(const Process& recipient) {

		}

		
	public:
		int id;
		bool down = false;
	};
public:
	BullyAlgSimulator(int numProcs) {

	}
	void Simulate(std::vector<int>& downProcs, int initiationProc) {
		// downing all downed processes
		for (auto& proc : processes) {
			if (std::ranges::find(downProcs, proc.id) == downProcs.end())
				proc.down = true;
		}

		// Get current coordinator
		auto curCoord = std::ranges::max_element(processes, std::less<int>(),
			[](const Process& p) { return p.id; }
		);
		// Current coordinator must be down
		assert(curCoord->down);

		auto curProc = std::ranges::find_if(processes,
			[initiationProc](const Process& p) { return p.id == initiationProc; }
		);

		std::cout << "P" << curProc->id << " sent message to P" << curCoord->id << '\n'
			<< "P" << curCoord->id << " is down and dosnt send response" << '\n'
			<< "P" << curProc->id << " Starts the election process" << '\n';


	}
private:
	std::vector<Process> processes;
	std::queue<Event> eventQueue;
};