// GABRIEL MALONE / CSCI 205 / LAB 3

#include <string>
#include <unordered_map>
#include <vector>
#include "Stack.hpp"


using namespace std;

// parenthesis balance checking
bool balanced(string const &expression){
	// return value
	bool balanced = true;
	// map of pairs
	unordered_map<char, char> bracket_pairs = {
			{')', '('},
			{']', '['},
			{'}','{'}
	};
	// vectors of expressions
	vector<char>leftBr = {'(', '[', '{'};
	vector<char>rightBr = {')', ']', '}'};
	// stacks to check for left - right balance
	Stack<char> openingBs;
	Stack<char> t_openingBs; // for even pair checks
	Stack<char> closingBs;
	// go through expression and get all the brackets
	// change this to use the map and then make a vector for each kind of bracket
	for (char c : expression){
		// check if c a left bracket
		if (std::find(leftBr.begin(), leftBr.end(),c) !=leftBr.end()){
			// push to opening brackets stack
			openingBs.push(c);
			t_openingBs.push(c);
		}
		// check if c a closing bracket
		// Runestone note:
		// Recall that each opening symbol is simply pushed on the stack
		// to wait for the matching closing symbol to appear later in the sequence.
		// When a closing symbol does appear, the only difference is that we must check
		// to be sure that it correctly matches the type of the opening symbol on top of the stack.
		if (std::find(rightBr.begin(), rightBr.end(),c) !=rightBr.end()){
			closingBs.push(c);
			if (openingBs.pop() != bracket_pairs[c]){
				return false;
			}
		}
	}
	// length check
	if (t_openingBs.stack_size() != closingBs.stack_size()){
		return false;
	}
	return balanced;
}

// convert infix to postfix notation
string infix_postfix(string const &infix) {
	// balanced bracket checking
	if (!balanced(infix)){
		throw std::invalid_argument("Error: Expression contains unbalanced brackets.");
	}

	// operator precedence map
	unordered_map<char, size_t> precedence = {
			{'+', 1},
			{'-', 1},
			{'*', 2},
			{'/', 2},
			{'(', 0},

	};
	// stack for operators
	Stack<char> operator_stack;
	// temp stack for iterating through entire stack via pops
	Stack<char> temp_stack;
	// instantiate final output
	string postfix;
	// iterate through infix input
	for (char c: infix) {
		if ( (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ) {
			// if 'c' an operand,
			// add to postfix string
			postfix += c;
		}
		if (c == '(')
			// if open parenthesis add to stack
			operator_stack.push(c);
		if (c == ')') {
			// if closed parenthesis pop stack
			// until reach open parenthesis
			while (operator_stack.peek() != '(') {
				postfix += operator_stack.pop();
			}
			// get rid of open parenthesis after
			if (operator_stack.peek() == '('){
				operator_stack.pop();
			}
		}
		// if an operator...
		if (precedence.find(c) != precedence.end()) {
			// push if higher precedence than current top of stack
			if (precedence[c] > precedence[operator_stack.peek()]) {
				operator_stack.push(c);
			}
				// Else, pop all the operators from the stack which are greater than
				// or equal in precedence to that of the scanned operator.
			else {
				while (!operator_stack.is_empty()){
					char op = operator_stack.pop();
					// If you encounter parenthesis while popping,
					// stop there and push the scanned operator on the stack.
					if (op == '(' || op == ')'){
						break;
					}
					if (precedence[op] >= precedence[c]){
						postfix += op;
					} else {
						//temp_stack.push(op);
					}
				}
				// push operator onto the stack
				operator_stack.push(c);
			}
		}
	}
	// put everything back after popping
	while (! temp_stack.is_empty()){
		operator_stack.push(temp_stack.pop());
	}
	// then pop and output from the stack
	// until it is not empty.
	while (! operator_stack.is_empty())
	{
		// don't include any parenthesis
		if (operator_stack.peek() != '(' || operator_stack.peek() != '(')
			postfix += operator_stack.pop();
		else
			// but do pop everything
			operator_stack.pop();
	}
	return postfix;
}

// evaluate postfix notation
int postfix_eval(string const &postfix){
	// stack to hold operands
	Stack<char> op_stack;
	// iterate through postfix left to right
	for (char c : postfix){
		if ( (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ) {
			// if 'c' an operand,
			// push to stack
			op_stack.push(c);
		}
		// for each operator
		if (c == '+' || c == '-' || c == '*' || c == '/') {
			// pop two operands from the stack
			int opA = op_stack.pop() - '0'; // convert char to int
			int opB = op_stack.pop() - '0'; // convert char to int
			int result;
			// apply the operator
			switch (c) {
				case '+':
					result = (opA + opB);
					break;
				case '-':
					result = (opB - opA);
					break;
				case '*':
					result = (opA * opB);
					break;
				case '/':
					result = (opB / opA);
			}
			op_stack.push(result + '0'); // convert int back to equivalent char
		}
	}
	return op_stack.pop() - '0'; // convert char to equivalent int
}

// direct infix evaluator
int infix_eval(string const &expression){
	string postfix = infix_postfix(expression);
	int result = postfix_eval(postfix);
	return result;
}