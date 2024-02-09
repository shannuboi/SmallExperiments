#pragma once


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return addTwoDigitsWithCarry(l1, l2, 0);
    }
private:
    ListNode* addTwoDigitsWithCarry(ListNode* l1, ListNode* l2, bool carry) {
        if (!l1 && !l2 && !carry) {
            return nullptr;
        }

        int val1 = l1 ? l1->val : 0;
        int val2 = l2 ? l2->val : 0;
        int sum = val1 + val2 + (int)carry;

        bool nextCarry = sum > 9;
        sum = nextCarry ? sum - 10 : sum;

        ListNode* next1 = l1 ? l1->next : nullptr;
        ListNode* next2 = l2 ? l2->next : nullptr;

        ListNode* sumNode = new ListNode(sum);
        sumNode->next = addTwoDigitsWithCarry(next1, next2, nextCarry);
        return sumNode;
    }
};