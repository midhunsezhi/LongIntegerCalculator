
#include "Node.cpp"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#ifndef DOUBLYLINKEDLIST_H_
#define DOUBLYLINKEDLIST_H_

class DoublyLinkedList
{
public:
	DoublyLinkedList();
	virtual ~DoublyLinkedList();
	struct node * head;
	struct node * tail;
	struct node * get( int index );
	struct node * getFirst();
	struct node * getLast();
	struct node * getNext( struct node * currentNode );
	struct node * getPrev( struct node * currentNode );
	void add( int index, int value );
	void addFirst( int value );
	void addLast( int value );
	bool isEmpty();
	void remove( int index );
	int size();
	int getNumberOfDigits();
	void setNumberOfDigits( int _length );
	string toString();
	void print();
	void empty();
	
private:
	int length;
	int no_of_digits;
	int max_digits;
};

#endif /*DOUBLYLINKEDLIST_H_*/
