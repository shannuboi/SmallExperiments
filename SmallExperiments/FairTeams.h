#pragma once

/*
https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/description/

2491. Divide Players Into Teams of Equal Skill

You are given a positive integer array skill of even length n where skill[i] denotes the skill of the ith player. Divide the players into n / 2 teams of size 2 such that the total skill of each team is equal.
The chemistry of a team is equal to the product of the skills of the players on that team.
Return the sum of the chemistry of all the teams, or return -1 if there is no way to divide the players into teams such that the total skill of each team is equal.

Example 1:
Input: skill = [3,2,5,1,3,4]
Output: 22
Explanation:
Divide the players into the following teams: (1, 5), (2, 4), (3, 3), where each team has a total skill of 6.
The sum of the chemistry of all the teams is: 1 * 5 + 2 * 4 + 3 * 3 = 5 + 8 + 9 = 22.

Example 2:
Input: skill = [3,4]
Output: 12
Explanation:
The two players form a team with a total skill of 7.
The chemistry of the team is 3 * 4 = 12.

Example 3:
Input: skill = [1,1,2,3]
Output: -1
Explanation:
There is no way to divide the players into teams such that the total skill of each team is equal.

Constraints:
2 <= skill.length <= 105
skill.length is even.
1 <= skill[i] <= 1000
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	long long dividePlayers(vector<int>& skill) {
		long long sumChemistry = 0;

		ranges::sort(skill);

		int neededTeamSkill = skill.front() + skill.back();
		sumChemistry += skill.front() * skill.back();

		for (size_t i = 1; i < skill.size() / 2; i++) {
			int curTeamSkill = skill[i] + skill[skill.size() - 1 - i];
			if (neededTeamSkill != curTeamSkill)
				return -1;

			sumChemistry += skill[i] * skill[skill.size() - 1 - i];
		}

		return sumChemistry;
	}
};

/*
Given an array of ints
Make pairs such that
	each pair has same sum
If pairing possible
	return sum of product of pairs
else
	return -1


Theory, have to pair highest w lowest
	given an array of ints with highest value M and smallest value m
	if M is paired with something other than m, 
	lets say M is paired w a and m is paired w b
		We know a > m and b < M thus
			(M + a) > (m + b)
			Which are not valis pairs
	thus by contridiction we know that M must pair with m or somethign equivilant
Theory correct

We have to pair largest with smallest
Once that pair is formed we can think of its ints as removed
The rest of the array is once again an array of int which we need to form into equal sum pairs
	Again have to pair largest w smalled

Alg 1:
	sort array
	pair first with last
		save sum
	from i = 1 till half way
		pair ith with -ith
			compare sum with saved sum
			if not same return -1

To calculate output lets alter alg to cal product as we make pairs
Alg 2:
	output = 0
	sort array
	pair first with last
		save sum
		output += product
	from i = 1 till half way
		pair ith with -ith
			compare sum with saved sum
			output += product
			if not same return -1
	return product

complexity:
	sorting + loop half the array
	= O(nlogn) + O(n)
	= O(nlogn)
*/