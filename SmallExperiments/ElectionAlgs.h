#pragma once

#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <iostream>
#include <assert.h>

class BullyAlgSimulator {
private:
	class Process {
	public:
		int id;
		int idCoord;
		bool isDown = false;
		int replyCount = 0;
	};


	class Event {
	public:
		enum class Type {
			Election, Ok, Coordinator
		};
	public:
		Event(Type type, Process* sending, Process* recieving)
			:	type(type),
				sending(sending),
				recieving(recieving) {
		}
		Type type;
		Process* sending;
		Process* recieving;
	};

public:
	BullyAlgSimulator(int numProcs) {
		for (int i = 0; i < numProcs; i++) {
			Process p;
			p.id = i;
			p.idCoord = numProcs - 1;
			processes.push_back(p);
		}
		PrintNetworkState();
	}
	void PrintNetworkState() {
		std::cout << "\n\tNetwork State:\n";
		for (const auto& p : processes) {
			std::cout << "P" << p.id << " is " << (p.isDown ? "down" : "up")
				<< (p.idCoord == p.id ? " and is coordinator\n" : "\n");
		}
		std::cout << '\n';
	}
	void Simulate(const std::vector<int>& downProcs, int initiationProc) {
		// downing all downed processes
		for (auto& p : processes) {
			p.replyCount = 0;
			if (std::ranges::find(downProcs, p.id) != downProcs.end())
				p.isDown = true;
		}

		// Get current coordinator
		auto curCoord = std::ranges::find_if(processes,
			[](const Process& p) { return p.id == p.idCoord; }
		);
		// Current coordinator must be isDown
		assert(curCoord->isDown);

		PrintNetworkState();

		auto curProc = std::ranges::find_if(processes,
			[initiationProc](const Process& p) { return p.id == initiationProc; }
		);

		std::cout << "P" << curProc->id << " sent message to P" << curCoord->id << '\n'
			<< "P" << curCoord->id << " is down and doesn't send response" << '\n'
			<< "P" << curProc->id << " starts the election process" << '\n' << '\n';

		// ELECTION PROCESS STARTS

		for (auto& p : processes)
			if (p.id > curProc->id)
				eventQueue.emplace(Event::Type::Election, curProc._Ptr, &p);

		while (!eventQueue.empty()) {
			Event curEvent = eventQueue.front();

			switch (curEvent.type)
			{
			case Event::Type::Election:
				HandleElectionMessage(curEvent.sending, curEvent.recieving);
				break;

			case Event::Type::Ok:
				HandleOkMessage(curEvent.sending, curEvent.recieving);
				break;

			case Event::Type::Coordinator:
				HandleCoordinatorMessage(curEvent.sending, curEvent.recieving);
				break;
			}

			eventQueue.pop();
		}
		PrintNetworkState();
	}

	void HandleElectionMessage(Process* sender, Process* reciever) {
		std::cout << "P" << sender->id << " sends election message to P" << reciever->id << '\n';
		sender->replyCount++;
		eventQueue.emplace(Event::Type::Ok, reciever, sender);
	}

	void HandleOkMessage(Process* sender, Process* reciever) {
		if (reciever->idCoord == reciever->id) return;
		if (sender->isDown) {
			reciever->replyCount--;
			if (reciever->replyCount == 0) {
				for (auto& p : processes)
					if (p.id != reciever->id)
						eventQueue.emplace(Event::Type::Coordinator, reciever, &p);
				reciever->idCoord = reciever->id;
			}
		}
		else {
			std::cout << "P" << sender->id << " sends OK reply to P" << reciever->id << '\n';

			for (auto& p : processes)
				if (p.id > sender->id)
					eventQueue.emplace(Event::Type::Election, sender, &p);
		}
	}

	void HandleCoordinatorMessage(Process* sender, Process* reciever) {
		if (!reciever->isDown) {
			std::cout << "P" << sender->id 
				<< " sends coordinator message to P" << reciever->id << '\n';
		}
		reciever->idCoord = sender->id;
	}
private:
	std::vector<Process> processes;
	std::queue<Event> eventQueue;
};