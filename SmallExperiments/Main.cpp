#include "IteratableBST.h"
#include <iostream>

template <class T>
void printTree(my::BinarySearchTree<T>& tree)
{
	// FOR EACH LOOP?!  OMG!!!!
	for (const T& e : tree) std::cout << e << " ";
	std::cout << '\n';
}

int main()
{
	my::BinarySearchTree<int> lol;
	printTree(lol);
	lol.Insert(5);
	printTree(lol);
	lol.Insert(7);
	printTree(lol);
	lol.Insert(10);
	printTree(lol);
}