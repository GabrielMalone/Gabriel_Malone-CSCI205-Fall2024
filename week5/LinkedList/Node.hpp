#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Node {
    public:
    T data;
    Node* next;
};

template <typename T>
void printNodes(Node<T>* n){
    while (n != NULL){
        cout << n->data << endl;
        n = n->next;
    }
}

template<typename T>
void insertNodeBetween(Node<T>* previousNode, T d){
    // create new Node
    Node<T>* newNode = new Node<T>();
    newNode->data = d;
    // point newNode at previous node's next
    newNode->next = previousNode->next;
    // point previous node at the new node
    previousNode->next = newNode;
}

// needs the address of the head pointer, then the data to be put into the new pointer
// address of the head pointer will be a pointer to a pointer
template <typename T, typename Q>
void insertNodeFront(Node<T>** head, Q d){
    // create a new node that will contain the data that is passed in
    Node<T>* newNode = new Node<T>();
    newNode->data = d;
    // place this new node in front of the current head
    // dereference the poiner-to-pointer-head
    newNode->next = *head;
    // set the newNode to be the new head
    *head = newNode;
}

template <typename T, typename Q>
void insertNodeBack(Node<T>** head, Q d){
    // create new Node that will contain data (d) 
    // passed in and be placed at back of linked list
    Node<T>* newBack = new Node<T>();
    // set data
    newBack->data = d;
     // point newBack at Null
    newBack->next = NULL;
    // check if list is empty
    // if empty, then new node is head node
    // and the first, last, and only node of list
    if (*head == NULL){
        *head = newBack;
        return; // nothing else to do at this point
    }
    // point old tail at new Back
    Node<T>* last = *head;
    while (last->next != NULL){
        last = last->next;
    }
    last-> next = newBack;
}

// int main(){

//     Node<int>* head = new Node<int>();
//     Node<int>* second = new Node<int>();
//     Node<int>* third = new Node<int>();

    
//     head -> data = 1;
//     head -> next = second;

//     second -> data = 2;
//     second -> next = third;

//     third -> data = 3;
//     third -> next = NULL;
    
//     // pass in the address of the current head pointer
//     insertNodeFront(&head, 30);
//     insertNodeFront(&head, 100);
//     insertNodeBack(&head, 1.1);
//     insertNodeBetween(second, -22);
//     printNodes(head);

//     return 0;
// }
