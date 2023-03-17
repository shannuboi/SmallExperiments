#include <iostream>
#include <random>
#include <vector>
#include <functional>
#include <chrono>
#include "FasterMultiplication.h"

template <typename T>
std::vector<T> GenarateArray(int SIZE, std::mt19937& rng, T smallest = (T)0, T largest = (T)100)
{
	std::uniform_int_distribution<T> dist(smallest, largest);
	std::vector<T> arr(SIZE);

	for (T& n : arr) n = dist(rng);

	return arr;
}

template <typename T, class multiplier>
void multiplyArrs(const std::vector<T>& arr1, const std::vector<T>& arr2, multiplier multiply)
{
	
}

int main()
{
	std::random_device rd;
	std::mt19937 rng;
	const int SIZE = 10000;
	std::vector<long long> arr1 = std::move( GenarateArray(SIZE, rng, (long long)1000000000000, (long long)1000000000000000) );
	std::vector<long long> arr2 = std::move( GenarateArray(SIZE, rng, (long long)1000000000000, (long long)1000000000000000) );

	auto before = std::chrono::steady_clock::now();					// Mark time b4
	for (int i = 0; i < std::min(arr1.size(), arr2.size()); i++)
	{
		KaratsubaMultiply(arr1[i], arr2[i]);
	}
	auto after = std::chrono::steady_clock::now();					// Mark time after

	std::chrono::duration<double> deltaT = after - before;		// Diff is time taken
	std::cout << "Time taken Karatsuba multiplication: " << deltaT.count() << "\n\n";


	before = std::chrono::steady_clock::now();						// Mark time b4
	for (int i = 0; i < std::min(arr1.size(), arr2.size()); i++)
	{
		arr1[i] * arr2[i];
	}
	after = std::chrono::steady_clock::now();						// Mark time after

	deltaT = after - before;										// Diff is time taken
	std::cout << "Time taken regular multiplication: " << deltaT.count() << "\n\n";
}