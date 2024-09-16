#include <iostream>
#include <string>
#include <unordered_map>
#include "Deque.h"
#include "Card.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

string postfixConversion(string exp);

int main(){
	// -------------------------------------------------------------------
	// BASE TESTS
	// -------------------------------------------------------------------
	// whitespace
	cout << endl;
	// Deque of strings
	Deque<string> names;
	names.push_front("bill");				// add item to front of deque
	names.push_front("ward");				//add item to front of deque
	while( !names.is_empty() ){				// while deque is not empty
		string temp = names.remove_front(); // get item from front of deque
		cout << "Name is: " << temp << endl;// print item
	}

	// Deque of integers
	Deque<int> nums;						// create deque of integers
	nums.push_back(1);						// add item to back of deque
	nums.push_back(2);						// add item to back of deque
	while( !nums.is_empty() ){				// while deque is not empty
		int a = nums.remove_back();			// get item from back of deque
		cout << "Number is: " << a << endl; // print item
	}

	// Deck of Card objects
	Deque<Card> deck;						// create deque of Card objects
	Card a('A', 'S');						// create Card object
	Card b('2', 'C');						// create Card object
	deck.push_front(a);						// add item to front of deque
	deck.push_front(b);						// add item to front of deque
	while( !deck.is_empty() ){				// while deque is not empty
		Card t = deck.remove_front();		// get item from front of deque
		cout << "Card is: " << t << endl;	// print item
	}
	// -------------------------------------------------------------------


	// -------------------------------------------------------------------
	// PUSH_FRONT TESTING + WRAP AROUND TESTING
	// -------------------------------------------------------------------
	// first for loop to fill deque without going over capacity
	// then a loop to print and confirm this works
	// second pair of for loops do the same but overfills capacity by 5
	// print loop confirms the overflow implemented correctly
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "PUSH FRONT TESTING " << endl;
	// -------------------------------------------------------------------
	cout << endl;
	
	// initialize deque
	Deque<int> nums2{10};
	int k = 0;
	// fill deque
	while (! nums2.is_full())
	{
		nums2.push_front(k);
		k++;
	}

	// show deque values
	for (int i = 0 ; i < nums2.size ; i ++)
	{
		cout << nums2[i] << ", ";
	}
	cout << endl;
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "PUSH FRONT TESTING + WRAP AROUND  " << endl;
	// -------------------------------------------------------------------
	cout << endl;

	// initialize new deck
	Deque<int> nums3{10};
	// fill deque beyond capacity (+5)
	for (int i = 0 ; i < nums3.capacity + 5; i ++)
	{
		nums3.push_front(i);
	}

	// show deque values
	for (int i = 0 ; i < nums3.capacity ; i ++)
	{
		cout << nums3[i] << ", ";
	}
	cout << endl;
	// -------------------------------------------------------------------


	// -------------------------------------------------------------------
	// REMOVE_FRONT TESTING + WRAP AROUND TESTING
	// -------------------------------------------------------------------
	// first for loop to fill deque without going over capacity
	// then a loop to print and confirm this works
	// second pair of for loops do the same but overfills capacity by 5
	// print loop confirms the overflow implemented correctly
	cout << endl;
	// -------------------------------------------------------------------
	cout << "REMOVE FRONT TESTING " << endl;
	// -------------------------------------------------------------------
	cout << endl;
	// -------------------------------------------------------------------
	cout << "fill deque with 'push_front()' " << endl;
	// -------------------------------------------------------------------
	// whitespace
	cout << endl;

	// intialize new deque
	Deque<int> numsA{10};
	// fill deque
	int j = 0;
	while (!numsA.is_full())
	{
		numsA.push_front(j);
		j ++;
	}

	// show deque
	for (int i = 0 ; i < numsA.size ; i ++)
	{
		cout << numsA[i] << ", ";
	}

	cout << endl;
	// whitespace
	cout << endl;
	// whitespace

	// call remove front for each item in deque until empty
	while (!numsA.is_empty())
	{
		cout << "removing item: " << numsA.remove_front() << endl;
	}

	cout << endl;
	// -------------------------------------------------------------------
	cout << "REMOVE FRONT TESTING + WRAP AROUND" << endl;
	// -------------------------------------------------------------------
	cout << endl;

	// intialize new deque
	Deque<int> numsB{10};

	// fill deque
	int l = 0;
	while (!numsB.is_full())
	{
		numsB.push_front(l);
		l ++;
	}

	// show deque
	for (int i = 0 ; i < numsB.size ; i ++)
	{
		cout << numsB[i] << ", ";
	}
	
	// whitespace
	cout << endl;
	// whitespace
	cout << endl;
	// whitespace

	// call remove front for each item in deque until empty
	// + beyond capacity to test wrap around
	for (int i = 0; i < numsB.capacity + 5 ; i ++)
	{
		cout << "removing item: " << numsB.remove_front() << endl;
	}
	// -------------------------------------------------------------------


	// -------------------------------------------------------------------
	// PUSH_BACK TESTING + WRAP AROUND TESTING
	// -------------------------------------------------------------------
	// first for loop to fill deque without going over capacity
	// then a loop to print and confirm this works
	// second pair of for loops do the same but overfills capacity by 5
	// print loop confirms the overflow implemented correctly
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "PUSH BACK TESTING " << endl;
	// -------------------------------------------------------------------
	cout << endl;

	// initialize new deque
	Deque<int> nums4{10};

	int q = 0;
	// fill deque
	while (! nums4.is_full())
	{
		nums4.push_back(q);
		q++;
	}
	
	// show deque's contents
	for (int i = 0 ; i < nums4.capacity ; i ++)
	{
		cout << nums4[i] << ", ";
	}

	cout << endl;
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "PUSH BACK TESTING + WRAP AROUND " << endl;
	// -------------------------------------------------------------------
	cout << endl;

	// initialize new deque
	Deque<int> nums5{10};

	// fill deck from back beyond deque's capacity (+5)
	for (int i = 0 ; i < nums5.capacity + 5; i ++)
	{
		nums5.push_back(i);
	}

	// show deque's contents
	for (int i = 0 ; i < nums5.capacity ; i ++)
	{
		cout << nums5[i] << ", ";
	}
	cout << endl;
	// -------------------------------------------------------------------


	// -------------------------------------------------------------------
	// REMOVE_BACK TESTING + WRAP AROUND TESTING
	// -------------------------------------------------------------------
	// first for loop to fill deque without going over capacity
	// then a loop to print and confirm this works
	// second pair of for loops do the same but overfills capacity by 5
	// print loop confirms the overflow implemented correctly
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "REMOVE BACK TESTING " << endl;
	// -------------------------------------------------------------------
	cout << endl;

	// initialize new deque
	Deque<int> nums6{10};

	// fill deque from back
	int w = 0;
	while (! nums6.is_full())
	{
		nums6.push_back(w);
		w ++ ;
	}
	
	// show deque's contents
	for (int i = 0 ; i < nums6.size ; i ++)
	{
		cout << nums6[i] << ", ";
	}

	// whitespace
	cout << endl;
	cout << endl;

	// call remove back for each item in deque until empty
	while (! nums6.is_empty())
	{
		cout << "removing item: " << nums6.remove_back() << endl;
	}

	// put everything back in 
	// fill deque from back
	w = 0;
	while (! nums6.is_full())
	{
		nums6.push_back(w);
		w ++ ;
	}

	// whitespace
	cout << endl;

	// show deque's contents
	for (int i = 0 ; i < nums6.size ; i ++)
	{
		cout << nums6[i] << ", ";
	}

	// whitespace
	cout << endl;
	cout << endl;

	// call remove front for each item in deque until empty
	// + beyond capacity to test wrap around
	for (int i = 0; i < nums6.capacity + 5 ; i ++)
	{
		cout << "removing item: " << nums6.remove_back() << endl;
	}
	// -------------------------------------------------------------------


	// -------------------------------------------------------------------
	// STACK TESTING
	// -------------------------------------------------------------------
	// first for loop to fill deque without going over capacity
	// then a loop to print and confirm this works
	// second pair of for loops do the same but overfills capacity by 5
	// print loop confirms the overflow implemented correctly
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "STACK TESTING " << endl;
	// -------------------------------------------------------------------
	cout << endl;

	Stack<string>s1{5};

	// fill stack
	s1.push("goob");
	s1.push("stella");
	s1.push("frank");
	s1.push("tarzan");
	s1.push("caesar");

	// show what's in stack
	// last item pushed should appear first
	for (int i = 0 ; i < s1.size ; i ++)
	{
		cout << s1[i] << endl;
	}

	// see if peek looks at correct element
	cout << endl;
	// -------------------------------------------------------------------
	cout << "PEEK TESTING " << endl;
	// -------------------------------------------------------------------
	cout << endl;
	// take a look 
	cout << "element to be popped next: " << s1.peek() << endl;

	// see if pop works
	cout << endl;
	// -------------------------------------------------------------------
	cout << "POP TESTING " << endl;
	// -------------------------------------------------------------------
	cout << endl;

	// pop last item entered into stack
	s1.pop();

	// add a new person
	s1.push("new guy");

	// see if it worked -> new guy should replace caesar
	for (int i = 0 ; i < s1.size ; i ++)
	{
		cout << s1[i] << endl;
	}

	// -------------------------------------------------------------------
	// QUEUE TESTING
	// -------------------------------------------------------------------
	// first for loop to fill deque without going over capacity
	// then a loop to print and confirm this works
	// second pair of for loops do the same but overfills capacity by 5
	// print loop confirms the overflow implemented correctly
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "ENQUEUE TESTING " << endl;
	// -------------------------------------------------------------------
	cout << endl;

	// instantate new queue
	Queue<int> q1 {10};

	// fill queue with enqueu
	for (int i = 1 ; i < q1.capacity+1; i ++)
	{
		q1.enqueu(i);
	}

	// see what's in queue
	for (int i = 0 ; i < q1.size; i ++)
	{
		cout << q1.array[i] << endl;
	}

	// test dequeue
	cout << endl;
	// -------------------------------------------------------------------
	cout << "DEQUEUE TESTING " << endl;
	// -------------------------------------------------------------------
	cout << endl;

	q1.dequeue();

	// see what's in queue
	for (int i = 0 ; i < q1.size ; i ++)
	{
		cout << q1.array[i] << endl;
	}


	// -------------------------------------------------------------------
	// POSTFIX TESTING
	// -------------------------------------------------------------------
	// first for loop to fill deque without going over capacity
	// then a loop to print and confirm this works
	// second pair of for loops do the same but overfills capacity by 5
	// print loop confirms the overflow implemented correctly
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "POSTFIX TESTING " << endl;
	// -------------------------------------------------------------------
	cout << endl;

	cout << postfixConversion("A+B*C") << endl;

	return 0;
}

string postfixConversion(string exp){
		// postfix expression string
		string pfexp = "";
		// precedence values for the operators.
		unordered_map<char, int> prec = {
			{'*',3},
			{'/',3},
			{'+',2},
			{'-',2},
			{'(',1}
		};
		// stack for keeping operators.
		Stack<char> opstackA;
		Stack<char> opstackB;
		// scan all the symbols from left to right 
		// in the given infix expression.
		for (char c : exp){
			// if the reading symbol is an operand, 
			// append it to the postfix expression.
			if ( ( c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') )
			{
				pfexp += c ;
			}
			// if the reading symbol is left parenthesis
			// ‘( ‘, push it onto the stack.
			if (c == '(')
			{
				opstackA.push(c);
			}
			// if the reading symbol is  ‘)’, 
			// then pop all the contents of the stack until 
			// the respective left parenthesis is popped and 
			// append each popped symbol to postfix expression.
			if (c == ')')
			{	
				// pop the ')'
				opstackA.pop();
				// get all the operators in the parenthesis
				while (!opstackA.is_empty())
				{
					char top = opstackA.peek();
					opstackA.pop();
					// if at the end , break out of loop
					if (top == '(')
					{	
						break;
					}
					pfexp += top;
				}
			}
			// if the reading symbol is ‘( ‘, 
			// then push it onto the stack.
			if (c == '(')
			{
				opstackA.push(c);
			}
			// if the reading symbol is an operator (+, –, *, /), 
			// then push it onto the stack. However, first, pop the operators 
			// which are already on the stack that have higher or equal precedence 
			// than the current operator and append them to the postfix. 
			// will need to utilize the two stacks to do this, I think.
			if (c == '+' || c == '-' || c == '*' || c ==  '/')
			{
				if (! opstackA.is_empty()){
					// if stack not empty, 
					// check it for higher precendence operators
					while (! opstackA.is_empty())
					{
						char stackA_symbol = opstackA.peek();
						opstackA.pop();
						// find higher precendence symbols 
						if (prec[stackA_symbol] >= prec[c])	
						{
							pfexp += stackA_symbol ;
						} else {
							// if not higher precendence,
							opstackB.push(c); 	
							// and take 'c' operator and push to stack A ?
							//  If an open parenthesis is there on top of the stack then push the operator into the stack.
							if (stackA_symbol != '(')	
								opstackB.push(stackA_symbol); // i dont know why this worked, was tinkering
						}
					}
					// refill stackA with the left-over- 
					// -symbols of lower precedence
					while (! opstackB.is_empty())
					{
						char stackB_symbol = opstackB.peek();
						opstackB.pop();
						opstackA.push(stackB_symbol);
					}
				// otherwise add operator to stack
				} else {
					opstackA.push(c);
				}
			}
		}
		// if the input is over, pop all the remaining 
		// symbols from the stack and append them to the postfix.
		while (! opstackA.is_empty())
		{
			char top = opstackA.peek();
			if (top != '(')
			{
				pfexp += top;
			}
			opstackA.pop();
		}
		return pfexp;
	}