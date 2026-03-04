#include "LLStack.h"

// Node constructor: initialize new nodes with an input string s
	// s should be stored as the data of the node
	// the nodes are not initially linked to any other node
	// so be sure that the "next" Node is linked to a nullptr
Node::Node(string s) 
{
	//assigs parameter to data 
	data = s;
	//holds the next linked node
	//first initialized as null to ensure that next is not pointing to any other memory that is unrelated to the node
	next = nullptr;
}

//constructor : initiazlize the head and tail field from LLStack class 
	// the stack should start with no items 
	// the head and tail should both be initialized as null pointers
LLStack::LLStack()
{
	//intially pointers are set to NULL because there are no nodes
	head = nullptr;
	tail = nullptr;
	count = 0;  //initialize to 0 because otherwise it will hold random junk and give issues for counter
}

//define the top() method, which will return the data at the top of the stack
//	(remember the "top" of the stack is the newest element)
//	If stack is empty, return "";
string LLStack::top()
{
	if(size() <= 0){
		return "";
	}
	else{
		//returns the data hold at the last node(head is same as top of stack in this case)
	return head->data;
	}
}

/*
	define the size() method, which will return the number of nodes in the stack
*/
int LLStack::size()
{
	return count;
}

/*
	- Create the new Node and initialize the fields of class Node (data and next)
	- update the head, tail and count accordingly

	Hint: To update head and tail properly, You have to consider two scenarios:
	1. If there is no element in the stack and this is the first one going to the stack
	2. If there is another head in the stack
*/
void LLStack::push(string s)
{
	//creates a new pointer for the new node
	Node* newNode = new Node(s);
	//newNode ->data = s; //stores string in new node
	newNode ->next=nullptr; //safety measure to make sure 
	
	if(head == nullptr){
		head = newNode;
		tail = newNode;
	}
	else{
		newNode->next = head; //makes the next node the previous head. In other words it stores the previous node before a new one was pushed
		//in this case imagine the list reading from left to right but new nodes are adding to the leftmost of the list.
		//this is why it is being labeled as next when really it's the previous node from the new one.

		head = newNode; //now the head (or top of stack) is pointing to the newly created node.
		
	}

	count++;

}

/*
	First, Check if the stack is empty or not. If not, update the head,tail and count accordingly.
		*Don't forget to release memory using delete
	Hint: To update head and tail properly, You should consider two different scenarios:
	1. If LLStack has more than one element
	2. If LLStack has exactly one element
*/
void LLStack::pop()
{
	if(head == nullptr){
		return;
	}

	//pointer to hold node that is to be deleted
Node* temp = head;

	if(head == tail){
		head = nullptr;
		tail = nullptr;
	}
	else{
		head = head->next;
	}

	//clears the memory for the removed node
	delete temp;
	count--;
}

/*
    define the removeAll() method, which removes all nodes 
    that have data equal to the given target string.
    - Traverse through the linked list
    - For each matching node, unlink it and delete it
    - Update head, tail, and count accordingly
    - Return how many nodes were removed

	Hints:
    ----------------------------------------
    - Always check if the list becomes empty after deletions (head == nullptr).
      If so, make sure tail is also set to nullptr.
    - Use a counter variable (such as 'removed') to track how many were deleted.
    - Be careful not to lose your place when deleting nodes:
        * Save curr->next in a temporary pointer before deleting curr.
    - Handle edge cases:
        * Stack is empty (no nodes to remove)
        * Target not found (return 0)
        * All nodes match the target (list becomes empty)
*/
int LLStack::removeAll(const string& target) 
{
	int removed = 0;
	Node* current = head;
	Node* prev = nullptr;

	while(current != nullptr){
		if(current->data == target){
			Node* temp = current;
			if(prev == nullptr){
				head = current->next;
				current = head;
			}
			else{
				prev->next = current->next;
				current = current->next;
			}
			delete temp;
			removed++;
			count--;
		}
		else{
			prev = current;
			current = current->next;
		}

	}
	if(head == nullptr){
		tail = nullptr;
	}
	else{
		tail = prev;
	}
	return removed;
}

