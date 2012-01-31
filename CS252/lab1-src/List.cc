//
// Implement the List class
//

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//
// Inserts a new element with value "val" in
// ascending order.
//
void
List::insertSorted( int val )
{
	if (val == NULL) {
		return;	
	}

	ListNode *curr = _head;
	ListNode *prev = NULL;
        
	while (curr != NULL) {
		if (curr->_value > val) break;

		prev = curr; 
		curr = curr->_next; 	
	}

	// creates new node
	// changes last->_next to new node
	ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
	newNode->_value = val;
	newNode->_next = curr;

	// assigns newNode._next to last->_next
	if (prev == NULL) {
		_head = newNode;			
	}
	else {
		prev->_next = newNode;		
	} 
}

//
// Inserts a new element with value "val" at
// the end of the list.
//
void
List::append( int val )
{
	ListNode *curr = _head;
	ListNode *prev = NULL;

	while (curr != NULL) {
		prev = curr;
		curr = curr->_next;	
	}

	ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
	newNode->_value = val;
	newNode->_next = curr;

	if (prev == NULL) {
		_head = newNode;
	}
	else {
		prev->_next = newNode;
	}
}

//
// Inserts a new element with value "val" at
// the beginning of the list.
//
void
List::prepend( int val )
{
	ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
	newNode->_value = val;
	newNode->_next = _head;
}

// Removes an element with value "val" from List
// Returns 0 if succeeds or -1 if it fails
int 
List:: remove( int val )
{
	if (val == NULL) return -1;

	ListNode *curr = _head;
	ListNode *prev = NULL;
	bool found = false;

	while (curr != NULL) {
		if (curr->_value == val) {
			found = true; 			
			break;
		}

		prev = curr;
		curr = curr->_next;	
	}

	if (found) {
		if (curr == _head) {
			_head = curr->_next;		
		}
		else {
			prev->_next = curr->_next;		
		}

		free(curr);
		return 0;	
	}
	else {
		return -1;
	}	
}

// Prints The elements in the list. 
void
List::print()
{
	ListNode *curr = _head;

	while (curr != NULL) {
		printf("%d\n", curr->_value);
		curr = curr->_next;	
	} 
}

//
// Returns 0 if "value" is in the list or -1 otherwise.
//
int
List::lookup(int val)
{
	ListNode *curr = _head;
	ListNode *prev = NULL;
	bool found = false;

	while (curr != NULL) {
		if (curr->_value == val) {
			found = true; 			
			break;
		}

		prev = curr;
		curr = curr->_next;	
	}

	if (found) {
		return 0;	
	}
	else {
		return -1;
	}
}

//
// List constructor
//
List::List()
{
  _head = NULL; 
}

//
// List destructor: delete all list elements, if any.
//
List::~List()
{
	ListNode *curr = _head;
	int valToRemove = 0;

	while (curr != NULL) {
		valToRemove = curr->_value;
		curr = curr->_next;

		remove(valToRemove);	
	}	
}

