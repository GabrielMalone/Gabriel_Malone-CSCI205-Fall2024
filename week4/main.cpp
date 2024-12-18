// GABRIEL MALONE // CSCI 205 / FALL 2024 / LAB 3

// COMPILE INSTRUCTIONS //
// g++ -o test main.cpp Task.cpp Card.cpp -g -std=c++17 -Wall -pedantic -std=c++17


#include <iostream>
#include <algorithm>
#include "Deque.hpp"
#include "Stack.hpp"
#include "Card.h"
#include "Queue.hpp"
#include "Task.h"
#include "infix_calculator.cpp"
#include "task_switching.cpp"

using namespace std;

string infix_postfix(string const &infix);
int postfix_eval(string const &postfix);
bool balanced(string const &expression);
int infix_eval(string const &expression);
void ringBuffer();

int main(){

	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "DEFAULT TESTS " << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	cout << endl;
	// Deque of strings
	Deque<string> names;
	names.push_front("bill");
	names.push_front("ward");
	while( !names.empty() ){
		string temp = names.pop_front();
		cout << "Name is: " << temp << endl;
	}

	// Deque of integers
	Deque<int> nums;
	nums.push_front(1);
	nums.push_front(2);
	while( !nums.empty() ){
		int a = nums.pop_front();
		cout << "Number is: " << a << endl;
	}

	// Deck of Card objects
	Deque<Card> deck;
	Card a('A', 'S');
	Card b('2', 'C');
	deck.push_front(a);
	deck.push_front(b);

	while( !deck.empty() ){
		Card t = deck.pop_front();
		cout << "Card is: " << t << endl;
	}

	// -------------------------------------------------------------------
	// PUSH_FRONT TESTING + RESIZE TESTING
	// -------------------------------------------------------------------
	// first for loop to fill deque without going over capacity
	// then a loop to print and confirm this works
	// overfill array to resize
	// print loop confirms the resize implemented correctly
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "PUSH FRONT TESTING ON DECK CAPACITY OF 10 " << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	cout << endl;

	// initialize deque
	Deque<int> nums2{10};
	int k = 0;
	// fill deque with ints 0-9
	while (! nums2.full())
	{
		nums2.push_front(k);
		k++;
	}

	// show deque values, should be 0-9 ascending
	for (size_t i = 0 ; i < nums2.getCapacity() ; i ++)
	{
		cout << nums2[i] << ", ";
	}
	cout << endl;
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "PUSH FRONT TESTING + RESIZE" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	cout << endl;
	// add beyond original deque's size
	nums2.push_front(10);
	// new deque capacity should now be double (20)
	cout << "new deck capacity: " << nums2.getCapacity() << endl;
	// whitespace
	cout << endl;
	// show deque values, should be 0-9 ascending
	for (size_t i = 0 ; i < nums2.getCapacity(); i ++)
	{
		cout << nums2[i] << ", ";
	}

	// loop for multiple resizes
	cout << endl;
	cout << endl;
	cout << "multiple resize testing" << endl;
	for (size_t i = 0 ; i < 99999; i ++)
	{
		nums2.push_front(1);
	}
	cout << "new deck capacity: " << nums2.getCapacity() << endl;

	// -------------------------------------------------------------------
	// LAB PDF TASK 1 DEQUE DEMO
	// -------------------------------------------------------------------
	//
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "DEQUE AFTER 6 PUSH (FRONT AND BACK) OPERATIONS " << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	cout << endl;
	// new deque
	Deque<int> labDeck{10};
	labDeck.push_front(42);
	labDeck.push_back(12);
	labDeck.push_back(27);
	labDeck.push_back(92);
	labDeck.push_front(86);
	labDeck.push_front(53);
	// show what's in deque
	for (size_t i = 0 ; i < labDeck.getCapacity() ; i ++)
	{
		cout << labDeck[i] << ", ";
	}
	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "POP_FRONT() OPERATION" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	cout << endl;
	// pop front
	cout << "current front element: " << labDeck.show_front() << endl;
	cout << "popping element: " << labDeck.pop_front() << endl;
	cout << "current front element: " << labDeck.show_front() << endl;
	cout << "no cycles spent zeroing or adjusting actual positions in array: ";
	// show what's in deque
	for (size_t i = 0 ; i < labDeck.getCapacity() ; i ++)
	{
		cout << labDeck[i] << ", ";
	}
	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "POP_BACK() + SHOW_BACK() OPERATION" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	// pop back
	cout << "current back element: " << labDeck.show_back() << endl;
	cout << "popping element: " << labDeck.pop_back() << endl;
	cout << "current back element: " << labDeck.show_back() << endl;
	cout << "no cycles spent zeroing or adjusting actual positions in array: ";
	// show what's in deque
	for (size_t i = 0 ; i < labDeck.getCapacity() ; i ++)
	{
		cout << labDeck[i] << ", ";
	}
	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "REMOVE_HEAD() OPERATION" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	// advances head forward
	cout << "current head element: " << labDeck.show_head() << endl;
	cout << "calling remove_head() ... " << endl;
	// call remove_head()
	labDeck.remove_head();
	cout << "current head element: "  << labDeck.show_head() << endl;
	cout << "current front element: " << labDeck.show_front() << endl;
	cout << "no cycles spent zeroing or adjusting actual positions in array: ";
	// show what's in deque
	for (size_t i = 0 ; i < labDeck.getCapacity() ; i ++)
	{
		cout << labDeck[i] << ", ";
	}
	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "PUSH_FRONT() OPERATION" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	labDeck.push_front(19);
	// show what's in deque, '19' should have overwritten '56'
	for (size_t i = 0 ; i < labDeck.getCapacity() ; i ++)
	{
		cout << labDeck[i] << ", ";
	}
	cout << endl;
	cout << "current head element: " << labDeck.show_head() << endl;
	cout << "current front element " << labDeck.show_front() << endl;
	// whitespace
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "A DECK MAY FIND ITSELF IN THIS SITUATION...WRAP AROUND TESTING + RESIZE" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	// set up the deque to be in situation as shown in lab pdf
	Deque<int>labDeck2{10};
	labDeck2.push_front(0);
	labDeck2.push_front(0);
	labDeck2.push_front(0);
	labDeck2.push_front(0);
	labDeck2.remove_head();
	labDeck2.remove_head();
	labDeck2.remove_head();
	labDeck2.remove_head();
	labDeck2.push_front(83);
	labDeck2.push_front(12);
	labDeck2.push_front(27);
	labDeck2.push_front(12);
	labDeck2.push_front(62);
	// confirm deque set up properly
	for (size_t i = 0 ; i < labDeck2.getCapacity() ; i ++)
	{
		cout << labDeck2[i] << ", ";
	}
	cout << endl;
	cout << "current head element: " << labDeck2.show_head()  << endl;
	cout << "current front element " << labDeck2.show_front() << endl;
	cout << "current tail element "  << labDeck2.show_tail()  << endl;
	cout << endl;
	cout << "push_front( 72 ) " << endl;
	labDeck2.push_front(72);
	// confirm deque set up properly
	for (size_t i = 0 ; i < labDeck2.getCapacity() ; i ++)
	{
		cout << labDeck2[i] << ", ";
	}
	cout << endl;
	cout << endl;
	cout << "push_front( 33 )  -- WRAP AROUND BEGINS" << endl;
	labDeck2.push_front(33);
	// confirm deque set up properly
	for (size_t i = 0 ; i < labDeck2.getCapacity() ; i ++)
	{
		cout << labDeck2[i] << ", ";
	}
	cout << endl;
	cout << endl;
	cout << "push_front( 99 )  -- WRAP AROUND CONTINUES" << endl;
	labDeck2.push_front(99);
	// confirm deque set up properly
	for (size_t i = 0 ; i < labDeck2.getCapacity() ; i ++)
	{
		cout << labDeck2[i] << ", ";
	}
	cout << endl;
	cout << endl;
	cout << "push_front() with wrap until resize called" << endl;
	labDeck2.push_front(44);
	labDeck2.push_front(31);
	labDeck2.push_front(58);
	// confirm deque set up properly
	for (size_t i = 0 ; i < labDeck2.getCapacity() ; i ++)
	{
		cout << labDeck2[i] << ", ";
	}

	cout << endl;
	cout << endl;
	cout << "push_front() continued..." << endl;
	labDeck2.push_front(91);
	labDeck2.push_front(84);
	labDeck2.push_front(77);
	// confirm deque set up properly
	for (size_t i = 0 ; i < labDeck2.getCapacity() ; i ++)
	{
		cout << labDeck2[i] << ", ";
	}

	cout << endl;
	cout << endl;
	cout << "push_back() testing after only pushing front to a resize REORGANiZE ARRAY" << endl;
	cout << "push_back ( 71 )" << endl;
	labDeck2.push_back(71);
	// confirm deque set up properly
	for (size_t i = 0 ; i < labDeck2.getCapacity() ; i ++)
	{
		cout << labDeck2[i] << ", ";
	}

	cout << endl;
	cout << endl;
	cout << "push_back() testing until resize, pushing back 6 more elements" << endl;
	cout << "order maintained after resize" << endl;
	labDeck2.push_back(21);
	labDeck2.push_back(31);
	labDeck2.push_back(41);
	labDeck2.push_back(51);
	labDeck2.push_back(61);
	labDeck2.push_back(65);
	// confirm deque set up properly
	cout << endl;
	for (size_t i = 0 ; i < labDeck2.getCapacity() ; i ++)
	{
		cout << labDeck2[i] << ", ";
	}
	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "TESTING THE REMAINING FUNCTIONS - ARRAY_SIZE" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	// array size should be 21 since 20 elements filled previous array, then one more to cause resize.
	cout << "Current array size :" << labDeck2.array_size()
	     << " vs current array capacity : "
	     << labDeck2.getCapacity() << endl;

	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "CONSTRUCT A DEQUE WITH ARRAY OF GIVEN ITEMS (int 1 - 4 ) AND SIZE (4)" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	// initialize new deque from an already existing array
	int arr[] = {1,2,3,4};
	size_t size = 4;
	Deque<int> deque(arr, size);
	// confirm deque set up properly
	cout << "new deque should have double capacity and all the original elements" << endl;
	cout << endl;
	for (size_t i = 0 ; i < deque.getCapacity() ; i ++)
	{
		cout << deque[i] << ", ";
	}

	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "STACK TESTING" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	// create new stack of strings
	Stack<string> stack1{5};
	stack1.push("goobert");
	stack1.push("tarl");
	stack1.push("dookus");
	stack1.push("quirk");
	stack1.push("bevis");
	// confirm stack set up properly
	for (size_t i = 0 ; i < stack1.stack_capacity() ; i ++)
	{
		cout << stack1[i] << ", ";
	}

	cout << endl;
	cout << endl;
	cout << "make sure LIFO is being followed. 'bevis' should be returned with peek()" << endl;
	cout << "calling peek(): " << stack1.peek() << endl;

	cout << endl;
	cout << "make sure LIFO is being followed. 'bevis' should be returned with pop()" << endl;
	cout << "calling pop(): " << stack1.pop() << endl;

	cout << endl;
	cout << "make sure LIFO is being followed. 'quirk' should now be returned with peek()" << endl;
	cout << "calling peek(): " << stack1.peek() << endl;

	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "STACK TESTING WITH OVERFLOW" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------

	cout << endl;
	cout << "make sure LIFO is being followed. pushing new element 'caesar' ";
	stack1.push("caesar");
	cout << "should overwrite bevis" << endl;
	cout << endl;
	// confirm stack set up properly
	for (size_t i = 0 ; i < stack1.stack_capacity() ; i ++)
	{
		cout << stack1[i] << ", ";
	}

	cout << endl;
	cout << endl;
	cout << "current stack size: " << stack1.stack_size() << endl;
	cout << "current stack capacity: " << stack1.stack_capacity() << endl;
	cout << "adding another element should cause resize" << endl;
	cout << endl;
	stack1.push("cleopatra");
	// confirm stack set up properly
	for (size_t i = 0 ; i < stack1.stack_capacity() ; i ++)
	{
		cout << stack1[i] << ", ";
	}
	cout << endl;
	cout << "current stack size: " << stack1.stack_size() << endl;
	cout << "current stack capacity: " << stack1.stack_capacity() << endl;

	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "QUEUE TESTING" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	// create a new queue with capacity of 5
	Queue<int> myQueue{5};
	// confirm this
	// confirm queue set up properly
	for (size_t i = 0 ; i < myQueue.queue_capacity() ; i ++)
	{
		cout << myQueue[i] << ", ";
	}
	cout << endl;
	cout << "current queue size: " << myQueue.queue_size() << endl;
	cout << "current queue capacity: " << myQueue.queue_capacity() << endl;

	// test enqueue
	cout << endl;
	cout << "call enqueue( 54 ),enqueue( 43 ),enqueue( 71 ), : " << endl;
	myQueue.enqueue(54);
	myQueue.enqueue(43);
	myQueue.enqueue(71);
	cout << "current queue size: " << myQueue.queue_size() << endl;
	// confirm queue set up properly
	for (size_t i = 0 ; i < myQueue.queue_capacity() ; i ++)
	{
		cout << myQueue[i] << ", ";
	}
	// dequeue testing
	cout << endl;
	cout << endl;
	cout << "calling dequeue() and returning element : "
	     << myQueue.dequeue()
	     << endl;
	cout << "current queue size: " << myQueue.queue_size() << endl;
	cout << "current queue capacity: " << myQueue.queue_capacity() << endl;

	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "INFIX TO POSTFIX TESTING" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	cout << "A + B - C = " ;
	cout << infix_postfix("A + B - C") << endl;

	cout << "A * B / C = " ;
	cout << infix_postfix("A * B / C") << endl;

	cout << "A + B * C = " ;
	cout << infix_postfix("A + B * C") << endl;

	cout << "A * B + C = " ;
	cout << infix_postfix("A * B + C") << endl;

	cout << "A * B + C * D = " ;
	cout << infix_postfix("A * B + C * D") << endl;

	cout << "(A + B) * (C + D) = " ;
	cout << infix_postfix("(A + B) * (C + D)") << endl;

	cout << "( ( A + B ) * C ) - D = " ;
	cout << infix_postfix("((A+B)*C)-D") << endl;

	cout << "A + B * (C - D / (E + F)) = " ;
	cout << infix_postfix("A + B * (C - D / (E + F))") << endl;

	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "POSTFIX EVAL TESTING" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	cout << postfix_eval("234*+5+") << endl;

	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "BALANCED BRACKETS TESTING" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	// balanced = 1
	cout << "Test balance of { { ( [ ] [ ] ) } ( ) } = ";
	cout << balanced("{ { ( [ ] [ ] ) } ( ) }") << endl;
	cout << "Test balance of [ [ { { ( ( ) ) } } ] ] = ";
	cout << balanced("[ [ { { ( ( ) ) } } ] ]") << endl;
	cout << "Test balance of [ [ { { ( ( ) ) } } ] ] = ";
	cout << balanced("[ ] [ ] [ ] ( ) { }") << endl;
	cout << endl;
	// unbalanced = 0
	cout << "Test balance of ( [ ) ] = ";
	cout << balanced("( [ ) ]") << endl;
	cout << "Test balance of ( ( ( ) ] ) ) = ";
	cout << balanced("( ( ( ) ] ) )") << endl;
	cout << "Test balance of [ { ( ) ] = ";
	cout << balanced("[ { ( ) ]") << endl;

	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "INFIX EVALUATION TESTING" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	cout << "evaluating: 6*2+3+2 = ";
	cout << infix_eval("6*2+3+2") << endl;
	cout << "evaluating: 6*(2+3)+2 = ";
	cout << infix_eval("6*(2+3)+2") << endl;
	cout << "evaluating: 6*(2+(3-2)) = ";
	cout << infix_eval("6*(2+(3-2))") << endl;
	cout << "evaluating: 6/(2+(3-2)) = ";
	cout << infix_eval("6/(2+(3-2))") << endl;

	// whitespace
	cout << endl;
	cout << endl;
	// -------------------------------------------------------------------
	cout << "-------------------------------------------------------------------" << endl;
	cout << "RING BUFFER TESTING" << endl;
	cout << "-------------------------------------------------------------------" << endl;
	// -------------------------------------------------------------------
	
	ringBuffer();

	return 0;
}




