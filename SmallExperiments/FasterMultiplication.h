#pragma once

#include <algorithm>
#include <math.h>
#include <iostream>
#include <random>
#include <vector>
#include <functional>
#include <chrono>

template <class T>
int GetNumOfDigits(const T& num, int base = 10)
{
	if (num == (T)0)
		return 1;

	for (int power = 0; true; power++)
		if (num / (T)pow(base, power) == (T)0) 
			return power;
}

template <class T>
int GetNumOfBits(T num)
{
	for (int bits = 0; true; bits++)
	{
		if (num == 0)
			return bits;
		num >>= 1;
	}
}

template <class T>
T KaratsubaMultiply(const T& a, const T& b)
{
	if (a < (T)2 && b < (T)2)
	{
		return a & b;
	}

	int halfbits = std::max(GetNumOfBits(a), GetNumOfBits(b)) / 2;

	T a0 = (((T)1 << halfbits) - 1) & a;
	T b0 = (((T)1 << halfbits) - 1) & b;
	T a1 = a >> halfbits;
	T b1 = b >> halfbits;

	T z0 = KaratsubaMultiply(a0, b0);
	T z1 = KaratsubaMultiply(a1, b1);
	T z2 = KaratsubaMultiply((a0 + a1), (b0 + b1));

	return z0 + ((z2 - z1 - z0) << halfbits) + (z1 << (2 * halfbits));
}

template <class T>
T KaratsubaMultiply(const T& a, const T& b, int base)
{
	if (a < (T)base || b < (T)base)
	{
		return a * b;
	}
}

template <typename T>
std::vector<T> GenarateArray(int SIZE, std::mt19937& rng, T smallest = (T)0, T largest = (T)100)
{
	std::uniform_int_distribution<T> dist(smallest, largest);
	std::vector<T> arr(SIZE);

	for (T& n : arr) n = dist(rng);

	return arr;
}

int RunTest()
{
	std::random_device rd;
	std::mt19937 rng;
	const int SIZE = 10000;
	std::vector<long long> arr1 = std::move(GenarateArray(SIZE, rng, (long long)1000000000000, (long long)1000000000000000));
	std::vector<long long> arr2 = std::move(GenarateArray(SIZE, rng, (long long)1000000000000, (long long)1000000000000000));

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