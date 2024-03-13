#include <iostream>
#include "ClockSyncAlgs.h"

int main() {
    std::cout << "CRISTIAN'S ALGORITHM\n";
    CristianAlg c;
    c.SetClientOffset(-3232);
    c.SetNetworkDelay(500);
    c.RunCristianAlgorithm();

    std::cout << "\n____________________________________________\n\n";
    std::cout << "BERKELEY'S ALGORITHM\n";

    const int NUM_CLIENT = 6;
    BerkeleyAlg b(NUM_CLIENT);
    b.SetClientOffsets({ 10000, 15000, -2000, -30000, 4000, 7500 });
    b.RunBerkeleyAlgorithm();
}