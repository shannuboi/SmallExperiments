#pragma once

#include <algorithm>
#include <math.h>

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