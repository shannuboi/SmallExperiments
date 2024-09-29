#pragma once

/*
https://leetcode.com/problems/coin-change-ii/description/

You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.

You may assume that you have an infinite number of each kind of coin.

The answer is guaranteed to fit into a signed 32-bit integer.


Example 1:

Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1


Example 2:

Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.


Example 3:

Input: amount = 10, coins = [10]
Output: 1


Constraints:
    1 <= coins.length <= 300
    1 <= coins[i] <= 5000
    All the values of coins are unique.
    0 <= amount <= 5000





make amt using coins

in ith coin
decision:
    take:
        amt > coins[i] -> 0
        amt <= coins[i] -> make amt - coins[i] using ith coin
OR
    skip:
        make amt using i+1th coin
*/


#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

using namespace std;

class Solution {
public:
    struct pair_hash {
        std::size_t operator()(const std::pair<int, int>& p) const {
            return std::hash<int>()(p.second) + 0x9e3779b9 + (std::hash<int>()(p.first) << 6) + (std::hash<int>()(p.first) << 2);
        }
    };
    std::unordered_map<std::pair<int,int>, int, pair_hash> lookupTable;
    vector<int> Coins;

    int change(int amount, vector<int>& coins) {
        Coins = coins;
        ranges::sort(Coins);
        
        return ChangeRecursive(amount, 0);
    }
    int ChangeRecursive(int amount, int curCoin) {
        if (curCoin == Coins.size())
            return amount == 0 ? 1 : 0;

        if (lookupTable.contains({ amount, curCoin }))
            return lookupTable[{amount, curCoin}];

        int combinations = 0;
        if (amount >= Coins[curCoin]) {
            combinations += ChangeRecursive(amount - Coins[curCoin], curCoin);
        }
        combinations += ChangeRecursive(amount, curCoin + 1);

        lookupTable[{amount, curCoin}] = combinations;
        return combinations;
    }
};