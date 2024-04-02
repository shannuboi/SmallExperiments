#pragma once

#include <string>
#include <iostream>
#include <algorithm>


template <typename T>
class Stack_arr
{
public:
	bool IsEmpty() const {
		return top == -1;
	}
	bool IsFull() const {
		return top == MaxCapacity - 1;
	}
	void Push(T value) {
		if (!IsFull()) {
			stack[++top] = value;
		}
	}
	int Pop() {
		if (!IsEmpty()) {
			return stack[top--];
		}
	}
	int Peek() const {
		if (!IsEmpty()) {
			return stack[top];
		}
	}
private:
	static constexpr int MaxCapacity = 128;
	T stack[MaxCapacity];
	int top = -1;
};


template <typename T>
class Stack_ll
{
private:
	class Node {
	public:
		T data;
		Node* next = nullptr;
	};
public:
	bool IsEmpty() const {
		return !top;
	}
	bool IsFull() const {
		return false;
	}
	void Push(T value) {
		Node* newnode = new Node;
		newnode->data = value;
		newnode->next = top;
		top = newnode;
	}
	int Pop() {
		if (!IsEmpty()) {
			Node* temp = top;
			top = top->next;
			int retVal = temp->data;
			delete temp;
			return retVal;
		}
	}
	int Peek() const {
		if (!IsEmpty()) {
			return top->data;
		}
	}
private:
	Node* top = nullptr;
};


bool BracesCheck(const std::string& expr) {
	Stack_arr<char> braces;
	Stack_arr<int> pos; // This stack is for getting pos of error

	for (int i = 0; i < expr.length(); i++) {
		if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') {
			braces.Push(expr[i]);
			pos.Push(i);
		}
		else if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}') {
			if (braces.IsEmpty()) {
				std::cout
					<< "This expression is NOT correct. Error at character #"
					<< i + 1 // counts from zero so add 1 for pos
					<< ". \'"
					<< expr[i]
					<< "\' - not opened.\n";
				return false;
			}

			char openBrace = braces.Pop();
			int bracepos = pos.Pop();
			if ((openBrace == '(' && expr[i] != ')') ||
				(openBrace == '[' && expr[i] != ']') ||
				(openBrace == '{' && expr[i] != '}')) {
				std::cout
					<< "This expression is NOT correct. Error at character #"
					<< bracepos + 1
					<< ". \'"
					<< openBrace
					<< "\' - not closed.\n";
				return false;
			}
		}
	}

	if (!braces.IsEmpty()) {
		char openBrace = braces.Pop();
		int bracepos = pos.Pop();
		std::cout
			<< "This expression is NOT correct. Error at character #"
			<< bracepos + 1
			<< ". \'"
			<< openBrace
			<< "\' - not closed.\n";
		return false;
	}

	std::cout << "This expression is correct.\n";
	return true;
}

bool IsCurOpPrecHigher(char cur, char top)
{
	if (cur == '(' || cur == '[' || cur == '{' ||
		top == '(' || top == '[' || top == '{') {
		return true;
	}
	else if (top == '^') {
		return false;
	}
	else if (top == '*' || top == '/') {
		return cur == '^';
	}
	else {
		return cur == '^' || cur == '*' || cur == '/';
	}
}

enum class OpType {
	All = 0,
	Brackets = 5,
	ClosingBrackets = 8
};

bool IsOperand(char op, OpType optype = OpType::All) {
	const char operators[11] = { '+', '-', '*', '/', '^', '(', '[', '{', '}', ']', ')' };

	return std::find(std::begin(operators) + (int)optype, std::end(operators), op) != std::end(operators);
}

std::string Convert2Postfix(const std::string& input) {
	std::string infix;
	std::string postfix;
	Stack_arr<char> stack;

	// Remove spaces from input
	std::copy_if(
		input.begin(), input.end(), std::back_inserter(infix),
		[](char c) {
			return c != ' ' && c != '\t';
		}
	);

	for (unsigned int i = 0; i < infix.length(); i++) {
		while (!IsOperand(infix[i]) && i < infix.length()) {
			//if cur char is not an operator
			postfix += infix[i++];
		}

		//if end reached then break
		if (i >= infix.length()) break;

		//If cur char isn’t bracket add space
		if (!IsOperand(infix[i], OpType::Brackets))
			postfix += " ";

		//if cur char is not }, ] or )
		if (!IsOperand(infix[i], OpType::ClosingBrackets)) {
			while (!stack.IsEmpty() && !IsCurOpPrecHigher(infix[i], stack.Peek())) {
				postfix += stack.Pop();
				postfix += " ";
			}
			stack.Push(infix[i]);
		}
		else { //if cur is closing bracket
			char top = stack.Pop();

			while (top != '(' && top != '[' && top != '{')
			{
				postfix += " ";
				postfix += top;
				top = stack.Pop();
			}
		}
	}

	postfix += " ";
	while (!stack.IsEmpty()) {
		postfix += stack.Pop();
		postfix += " ";
	}

	return postfix;
}

void RunBraceCheckerTest() {
	const std::string expr1 = "1+2*(3/4)";
	const std::string expr2 = "1+2*[3*3+{4-5(6(7/8/9)+10)-11+(12*8)]+14";
	const std::string expr3 = "1+2*[3*3+{4-5(6(7/8/9)+10)}-11+(12*8)/{13 +13}]+14";

	std::cout << expr1 << '\n';
	BracesCheck(expr1);
	std::cout << '\n' << expr2 << '\n';
	BracesCheck(expr2);
	std::cout << '\n' << expr3 << '\n';
	BracesCheck(expr3);
}

void RunConvert2PostfixTest() {
	const std::string expr1 = "10+3-5";
	const std::string expr2 = "12+30/5";
	const std::string expr3 = "430+10^3";
	const std::string expr4 = "{2*(430+10)}^3";

	std::cout << expr1 << '\n';
	std::cout << Convert2Postfix(expr1) << "\n\n";
	std::cout << expr2 << '\n';
	std::cout << Convert2Postfix(expr2) << "\n\n";
	std::cout << '\n' << expr3 << '\n';
	std::cout << Convert2Postfix(expr3) << "\n\n";
	std::cout << '\n' << expr4 << '\n';
	std::cout << Convert2Postfix(expr4) << "\n\n";
}