#include <iostream>
#include "ElectionAlgs.h"

int main()
{
	const int NumProcs = 7;
	RingAlgSimulator ringAlg(NumProcs);
	std::cout << "\n\t\t> Processes P6 and P5 fail <\n";
	ringAlg.Simulate({ 6,5 }, 2);

	std::cout << "\n\t\t> Now further process P4 fails <\n";
	ringAlg.Simulate({ 4 }, 2);
}