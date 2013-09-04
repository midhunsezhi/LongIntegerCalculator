
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include "DoublyLinkedList.h"

#ifndef LONGINT_H_
#define LONGINT_H_

using namespace std;

class LongInt
{
public:
	LongInt();
	LongInt( char sign, string value );
	virtual ~LongInt();
	char getSign();
	LongInt add( LongInt _value );
	LongInt sub( LongInt _value );
	LongInt mult( LongInt _value );
	LongInt div( LongInt _value );
	LongInt pow( unsigned long int exponent );
	bool isGreaterThan( LongInt _value );
	void normalize();
	DoublyLinkedList getList();
	string getValue();
	void setSign( char _sign );
	void setValue( string _value );
	void parse();
	long int getOverflow( struct node * currentNode );
	void print();
	string toString();
	
private:
	DoublyLinkedList * list;
	char sign;
	string value;
	int max_digits;
	LongInt add( LongInt operand1, LongInt operand2 );
	LongInt sub( LongInt operand1, LongInt operand2 );
};

#endif /*LONGINT_H_*/
