
#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList()
{
	// Initialize head and tail

	head = new struct node;
	tail = new struct node;

	// Data

	head->data = -1;
	tail->data = -1;

	// Links

	head->prev = NULL;
	head->next = tail;

	head->prev = head;
	tail->next = NULL;

	// Node length and int length

	length = 0;
	no_of_digits = 0;
	max_digits = 4;

}

DoublyLinkedList::~DoublyLinkedList()
{
	head = NULL;
	tail = NULL;
	
	delete head;
	delete tail;
}

struct node * DoublyLinkedList::getNext( struct node * currentNode )
{

	return currentNode->next;

}

struct node * DoublyLinkedList::getPrev( struct node * currentNode )
{

	return currentNode->prev;

}

struct node * DoublyLinkedList::getFirst()
{
	return get(0);
}

struct node * DoublyLinkedList::getLast()
{
	return get( length );
}

struct node * DoublyLinkedList::get( int index )
{
	if ( index < 0 || index > length ) {

		cout << "ERROR - Invalid node index [get method]" << endl;
		return 0;

	}

	node * cursor = head;

	for ( int i = 0; i < index; i++ ) {

		cursor = cursor->next;

	} // end for loop

	return cursor;

}

void DoublyLinkedList::add( int index, int value )
{
	struct node * cursor = get(index);
	struct node * temp = new struct node;

	temp->data = value;
	temp->prev = cursor;
	temp->next = cursor->next;
	cursor->next->prev = temp;
	cursor->next = temp;
	length++;
}

void DoublyLinkedList::addFirst( int value )
{
	struct node * cursor = head;
	struct node * temp = new struct node;

	temp->data = value;
	temp->prev = cursor;
	temp->next = cursor->next;
	cursor->next->prev = temp;
	cursor->next = temp;
	length++;

}

void DoublyLinkedList::addLast( int value )
{
	struct node * cursor = tail->prev;
	struct node * temp = new struct node;

	temp->data = value;
	temp->prev = cursor;
	temp->next = cursor->next;
	cursor->next->prev = temp;
	cursor->next = temp;
	length++;
}

bool DoublyLinkedList::isEmpty()
{
	return length == 0;
}

void DoublyLinkedList::remove( int index )
{
	if ( index == 0 ) {

		cout << "ERROR - Invalid node index [remove method]." << endl;

	} else {

		struct node * result = get( index );
		result->next->prev = result->prev;
		result->prev->next = result->next;
		length--;

	}

}

void DoublyLinkedList::empty()
{
	
	head->prev = NULL;
	head->next = tail;

	head->prev = head;
	tail->next = NULL;

	length = 0;
	no_of_digits = 0;

}

int DoublyLinkedList::size()
{
	struct node * current = head;

	while ( current->next != tail ) {

		current = current->next;
		length = length + 1;

	}
	
	return length;
}

int DoublyLinkedList::getNumberOfDigits()
{
	return no_of_digits;
}

void DoublyLinkedList::setNumberOfDigits( int _length )
{
	no_of_digits = _length;
}

string DoublyLinkedList::toString()
{
	string tostring = "[HEAD] - ";

	struct node * current = head;

	while ( current->next != tail ) {

		current = current->next;
		long int data = current->data;

		// Get # of leading zeros

		int zeros = 0;

		// Only do this if there is a previous node

		if ( current->prev->data >= 0 ) {

			ostringstream o;
			o << data;
			int size = o.str().size();
			zeros = max_digits - size;

		}

		// Convert to string

		string s;
		stringstream out;
		out << data;
		s = out.str();

		// Add leading zeros, if any

		for ( int i = 0; i < zeros; i++ ) {

			s = "0" + s;

		}

		// Concatenate

		tostring = tostring + "[" + s + "] - ";

	}

	tostring = tostring + "[TAIL]";

	return tostring;
}

void DoublyLinkedList::print()
{
	string toprint = toString();
	cout << toprint << endl;
}
