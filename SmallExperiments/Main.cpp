#include <iostream>
#include <string>
#include "DoublyLinkedList.h"
#include <algorithm>
#include <iterator>

template <class T>
void PrintList(const DoublyLinkedList<T>& list) {
	std::copy( list.begin(), list.end(), std::ostream_iterator<T>(std::cout, " ") );
	std::cout << '\n';
}

int main() {
	DoublyLinkedList<int> l;
	PrintList(l);
	l.PushBack(1);
	PrintList(l);
	l.PushBack(2);
	PrintList(l);
	l.PushFront(3);
	PrintList(l);
	l.AddAfter(l.begin(), 4);
	PrintList(l);
	l.AddAfter(l.end(), 5);
	PrintList(l);
	l.AddBefore(l.begin(), 6);
	PrintList(l);
	l.AddBefore(l.end(), 7);
	PrintList(l);
	l.AddAfter(++l.begin(), 8);
	PrintList(l);
}