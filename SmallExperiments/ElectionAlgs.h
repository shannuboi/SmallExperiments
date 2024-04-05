#pragma once

#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <iostream>
#include <assert.h>

class RingAlgSimulator {
private:
	class Process {
	public:
		int id;
		int idCoord;
		bool isDown = false;
		bool sentMessage = false;
	};

	class Event {
	public:
		enum class Type {
			Election, Coordinator
		};
	public:
		Event(Type type, std::string& msg, Process* sending, Process* recieving)
			: type(type),
			message(msg),
			sending(sending),
			recieving(recieving) {
		}
		Type type;
		std::string message;
		Process* sending;
		Process* recieving;
	};
public:
	RingAlgSimulator(int numProcs) {
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
				<< ((!p.isDown && p.idCoord == p.id) ? " and is coordinator\n" : "\n");
		}
		std::cout << '\n';
	}
	void Simulate(const std::vector<int>& downProcs, int initiationProc) {
		// downing all downed processes
		for (auto& p : processes) {
			p.sentMessage = false;
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

		auto succ = GetSuccessor(curProc._Ptr);
		std::string msg = "P" + std::to_string(curProc->id);
		eventQueue.emplace(Event::Type::Election, msg, curProc._Ptr, succ);

		while (!eventQueue.empty()) {
			Event curEvent = eventQueue.front();

			switch (curEvent.type)
			{
			case Event::Type::Election:
				HandleElectionMessage(curEvent.message, curEvent.sending, curEvent.recieving);
				break;

			case Event::Type::Coordinator:
				HandleCoordinatorMessage(curEvent.message, curEvent.sending, curEvent.recieving);
				break;
			}

			eventQueue.pop();
		}
		PrintNetworkState();
	}
	Process* GetSuccessor(Process* proc) {
		auto cur = std::ranges::find(processes, proc->id, [](const Process& p) { return p.id; });

		do {
			cur++;
			if (cur == processes.end()) cur = processes.begin();
		} while (cur->isDown);

		return cur._Ptr;
	}
	void HandleElectionMessage(std::string msg, Process* sender, Process* reciever) {
		std::cout << "P" << sender->id << " sends Election message to P" << reciever->id 
			<< " with message [" << msg << "]\n";
		std::string recieverID = "P" + std::to_string(reciever->id);
		auto succ = GetSuccessor(reciever);
		// If recieverID not in msg
		if (std::ranges::search(msg, recieverID).begin() == msg.end()) {
			msg += " " + recieverID;
			eventQueue.emplace(Event::Type::Election, msg, reciever, succ);
		}
		else {
			int maxID = -1;
			for (int i = 0; i < msg.size();) {
				std::string curID;
				if (msg[i] == 'P') {
					i++;
					while (i < msg.size() && msg[i] != ' ') {
						curID += msg[i];
						i++;
					}
					maxID = std::max(maxID, std::stoi(curID));
				}
				else i++;
			}
			reciever->idCoord = maxID;
			std::string newMessage = std::to_string(maxID);
			eventQueue.emplace(Event::Type::Coordinator, newMessage, reciever, succ);
			reciever->sentMessage = true;
		}
	}
	void HandleCoordinatorMessage(std::string msg, Process* sender, Process* reciever) {
		std::cout << "P" << sender->id << " sends Coordinator message to P" << reciever->id
			<< " with message [P" << msg << "]\n";
		int coordID = std::stoi(msg);
		if (!reciever->sentMessage) {
			reciever->idCoord = coordID;
			auto succ = GetSuccessor(reciever);
			eventQueue.emplace(Event::Type::Coordinator, msg, reciever, succ);
			reciever->sentMessage = true;
		}
	}

private:
	std::vector<Process> processes;
	std::queue<Event> eventQueue;
};

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