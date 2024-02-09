#include <iostream>

void lmao(int** x) {
	std::cout << x << ": " << *x << ": " << **x << '\n';
	auto hold = x;
	int garbage = 69;
	int* nice = &garbage;

	x = &nice;

	std::cout << x << ": " << *x << ": " << **x << '\n';
	auto temp = *x;
	int haha = 420;

	*x = &haha;

	std::cout << x << ": " << *x << ": " << **x << '\n';
	int buffer = **x;
	int bitch = 666;

	**x = bitch;

	std::cout << x << ": " << *x << ": " << **x << '\n';
}

int main()
{
	int a = 1;
	int* ap = &a;
	int** x = &ap;
	std::cout << x << ": " << *x << ": " << **x << '\n';
	lmao(x);
	std::cout << x << ": " << *x << ": " << **x << '\n';
}