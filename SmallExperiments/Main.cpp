#include "CoinChange2.h"
#include <iostream>

int main() {
	Solution s;
	vector coins = { 
		1,2,5
	};
	std::cout << s.change(500, coins);
}