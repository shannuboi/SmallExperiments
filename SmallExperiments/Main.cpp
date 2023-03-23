#include <iostream>
#include "RedBlackTree.h"

class A {
public:
	void Foo() {
		std::cout << "Foo()\n";
	}
};

class B {
public:
	A* operator->() {
		return a;
	}
	A* a;
};

int main() {
	A a;
	B b = { &a };
	b->Foo(); 
}