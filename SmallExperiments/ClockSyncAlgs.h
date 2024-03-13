#pragma once

#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>
#include <random>

namespace C = std::chrono;

class CristianAlg {
public:
	typedef C::hh_mm_ss<C::milliseconds> Clock;

public:
	CristianAlg() :
		networkDelay(C::milliseconds::zero()),
		clientOffset(C::milliseconds::zero()) {}
	void SetNetworkDelay(int milliseconds) {
		networkDelay = C::milliseconds(milliseconds);
	}
	void SetClientOffset(int milliseconds) {
		clientOffset = C::milliseconds(milliseconds);
	}
	void RunCristianAlgorithm() const {
		auto start = C::system_clock::now();

		Clock T0 = GetClientTime();
		std::cout << "\t\t\t\t>> Client requests servers for its clock time\n";
		std::cout << "Client clock (T0): " << T0 << '\n';

		Clock serverClock = ServerSendResponse();

		Clock T1 = GetClientTime();
		std::cout << "\t\t\t\t>> Client recieves response after some delay\n";
		std::cout << "Client clock (T1): " << T1 << '\n';

		auto end = C::system_clock::now();

		auto responseTime = T1.to_duration() - T0.to_duration();
		auto correctedClientTime = Clock(serverClock.to_duration() + responseTime / 2);

		std::cout << "\nClient clock after currection: " << correctedClientTime << '\n';
	}

private:
	Clock ServerSendResponse() const {
		// Delay
		std::this_thread::sleep_for(networkDelay);

		Clock serverClock = GetServerTime();
		std::cout << "\t\t\t\t Server recives the request and gets time <<\n";
		std::cout << "Server clock: " << serverClock << '\n';
		std::cout << "\t\t\t\t Server sends response containing its clock <<\n";

		// Delay
		std::this_thread::sleep_for(networkDelay);

		return serverClock;
	}
	Clock GetServerTime() const {
		auto curDateTime = 
			C::zoned_time(C::current_zone(), C::system_clock::now()).get_local_time();
		auto curDate = C::floor<C::days>(curDateTime);
		auto curTime = C::floor<C::milliseconds>(curDateTime - curDate);

		return Clock(curTime);
	}
	Clock GetClientTime() const {
		return Clock(GetServerTime().to_duration() + clientOffset);;
	}

private:
	C::milliseconds networkDelay; 
	C::milliseconds clientOffset;
};



class BerkeleyAlg {
public:
	typedef C::hh_mm_ss<C::milliseconds> Clock;

public:
	BerkeleyAlg(int nClients) : 
			NUM_CLIENTS(nClients) {
		clientOffsets.assign(NUM_CLIENTS, C::milliseconds::zero());
	}
	void SetClientOffsets(std::vector<int> milliseconds) {
		assert(NUM_CLIENTS == milliseconds.size());
		std::ranges::transform(
			milliseconds, clientOffsets.begin(),
			[](int ms) { return C::milliseconds(ms); }
		);
	}
	void RunBerkeleyAlgorithm() const {
		std::cout << "Selecting master\n";
		int master = SelectMaster();
		Clock masterClock = GetClientTime(master);
		std::cout << "Client" << master << " is master\n\n";

		std::vector<Clock> slaveTimes;
		C::milliseconds sum = C::milliseconds::zero();
		for (int i = 0; i < NUM_CLIENTS; i++) {
			if (i == master) {
				slaveTimes.push_back(masterClock);
				continue;
			}

			auto c = GetClientTime(i);
			std::cout 
				<< ">> Client" << i << " sends its time, " 
				<< c << ", to master\n";

			auto timediff = masterClock.to_duration() - c.to_duration();
			std::cout 
				<< ">> Master saves the time difference: " 
				<< timediff << '\n';
			slaveTimes.push_back(c);
			sum += timediff;
		}
		std::cout << '\n';

		C::milliseconds avg = sum / NUM_CLIENTS;
		std::cout 
			<< ">> Master calculates the avg time difference: " 
			<< avg << '\n';

		Clock newMasterClock = Clock(GetClientTime(master).to_duration() + avg);
		std::cout 
			<< ">> Master sets its time to " 
			<< newMasterClock << '\n';

		std::vector<C::milliseconds> slaveTimeDeltas;
		for (int i = 0; i < NUM_CLIENTS; i++) {
			if (i == master) {
				slaveTimeDeltas.push_back(C::milliseconds::zero());
				continue;
			}
			auto deltaT = newMasterClock.to_duration() - slaveTimes[i].to_duration();
			std::cout 
				<< ">> Masters sends time difference " 
				<< deltaT << " to Client" << i << '\n';		
			slaveTimeDeltas.push_back(deltaT);
		}
		std::cout << '\n';

		for (int i = 0; i < NUM_CLIENTS; i++) {
			if (i == master) continue;
			Clock newClientClock = Clock(GetClientTime(i).to_duration() + slaveTimeDeltas[i]);
			std::cout 
				<< ">> Client" << i << " sets its clock to "
				<< newClientClock << '\n';
		}
	}

private:
	int SelectMaster() const {
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> dist(0, NUM_CLIENTS);

		return dist(rng);
	}
	Clock GetActualTime() const {
		auto curDateTime = 
			C::zoned_time(C::current_zone(), C::system_clock::now()).get_local_time();
		auto curDate = C::floor<C::days>(curDateTime);
		auto curTime = C::floor<C::milliseconds>(curDateTime - curDate);

		return Clock(curTime);
	}
	Clock GetClientTime(int index) const {
		return Clock(GetActualTime().to_duration() + clientOffsets.at(index));
	}

private:
	const int NUM_CLIENTS;
	std::vector<C::milliseconds> clientOffsets;
};