
#include "LongInt.h"
#include <iostream>
#include <sstream>

using namespace std;

void add();
void subtract();
void multiply();
void divide();
void power();
void givenData();
void getSelection();
void askForMore();
void exit();
void test();
int main();

void multiply()
{
	char sign1;			// Operand 1 sign
	char sign2;			// Operand 2 sign

	string operand1;	// String representation of operand 1
	string operand2;	// String representation of operand 2

	LongInt * op1;		// LongInt operand 1
	LongInt * op2;		// LongInt operand 2
	LongInt * product;	// LongInt product

	char value1[255];	// Buffer for 1st operand input
	char value2[255];	// Buffer for 2nd operand input

	// Fill arrays with default data

	for ( int i = 0; i < 255; i++ ) {

		value1[i] = '\0';
		value2[i] = '\0';

	}

	// Get first operand

	bool valid = false;

	while ( !valid ) {

		cout << "Input the first operand for MULTIPLY (e.g. +12345678): ";
		cin >> value1;
		sign1 = value1[0];

		for ( int i = 1; i <= 255; i++ ) {

			// Don't include null

			if ( value1[i] != '\0' ) {

				// Must be a number

				if ( value1[i] == '0' || value1[i] == '1' || value1[i] == '2' 
					|| value1[i] == '3' || value1[i] == '4' || value1[i] == '5'
						|| value1[i] == '6' || value1[i] == '7' || value1[i] == '8'
							|| value1[i] == '9' ) {

					operand1 = operand1 + value1[i];

					valid = true;

				} else {

					cout << "\n*** Error: Invalid input. Please enter a sign followed by a number. ***\n" << endl;
					valid = false;
					break;

				} // end if

			} // end if

		} // end for loop

	} // end while loop

	valid = false; // Reset valid flag for second operand

	// Get second operand

	while ( !valid ) {

		cout << "Input the second operand for MULTIPLY (e.g. +12345678): ";
		cin >> value2;
		sign2 = value2[0];

		for ( int i = 1; i <= 255; i++ ) {

			// Don't include null

			if ( value2[i] != '\0' ) {

				// Must be a number

				if ( value2[i] == '0' || value2[i] == '1' || value2[i] == '2' 
					|| value2[i] == '3' || value2[i] == '4' || value2[i] == '5'
						|| value2[i] == '6' || value2[i] == '7' || value2[i] == '8'
							|| value2[i] == '9' ) {

					operand2 = operand2 + value2[i];

					valid = true;

				} else {

					cout << "\n*** Error: Invalid input. Please enter a sign followed by a number. ***\n" << endl;
					valid = false;
					break;

				} // end if

			} // end if

		} // end for loop

	} // end while loop

	// Set up LongInt structures

	op1 = new LongInt( sign1, operand1 );	// Operand 1
	op2 = new LongInt( sign2, operand2 );	// Operand 2
	product = new LongInt;					// Product

	// Call to multiplication

	*product = op1->mult( *op2 );			// Product = Operand1 * Operand2

	// Print result

	cout << "Result: (" << sign1 << ") " << operand1 << " * (" << sign2 << ") " << operand2 << " = (" << product->getSign() << ") " << product->getValue() << endl;

	// See if user wants to do more

	askForMore();
}

void divide()
{
	char sign1;			// Operand 1 sign
	char sign2;			// Operand 2 sign

	string operand1;	// String representation of operand 1
	string operand2;	// String representation of operand 2

	LongInt * op1;		// LongInt operand 1
	LongInt * op2;		// LongInt operand 2
	LongInt * quotient;	// LongInt product

	char value1[255];	// Buffer for 1st operand input
	char value2[255];	// Buffer for 2nd operand input

	// Fill arrays with default data

	for ( int i = 0; i < 255; i++ ) {

		value1[i] = '\0';
		value2[i] = '\0';

	}

	// Get first operand

	bool valid = false;

	while ( !valid ) {

		cout << "Input the first operand (DIVIDEND) for DIVIDE (e.g. +12345678): ";
		cin >> value1;
		sign1 = value1[0];

		for ( int i = 1; i <= 255; i++ ) {

			// Don't include null

			if ( value1[i] != '\0' ) {

				// Must be a number

				if ( value1[i] == '0' || value1[i] == '1' || value1[i] == '2' 
					|| value1[i] == '3' || value1[i] == '4' || value1[i] == '5'
						|| value1[i] == '6' || value1[i] == '7' || value1[i] == '8'
							|| value1[i] == '9' ) {

					operand1 = operand1 + value1[i];

					valid = true;

				} else {

					cout << "\n*** Error: Invalid input. Please enter a sign followed by a number. ***\n" << endl;
					valid = false;
					break;

				} // end if

			} // end if

		} // end for loop

	} // end while loop

	valid = false; // Reset valid flag for second operand

	// Get second operand

	while ( !valid ) {

		cout << "Input the second operand (DIVISOR) for DIVIDE (e.g. +12345678): ";
		cin >> value2;
		sign2 = value2[0];

		for ( int i = 1; i <= 255; i++ ) {

			// Don't include null

			if ( value2[i] != '\0' ) {

				// Must be a number

				if ( value2[i] == '0' || value2[i] == '1' || value2[i] == '2' 
					|| value2[i] == '3' || value2[i] == '4' || value2[i] == '5'
						|| value2[i] == '6' || value2[i] == '7' || value2[i] == '8'
							|| value2[i] == '9' ) {

					operand2 = operand2 + value2[i];

					valid = true;

				} else {

					cout << "\n*** Error: Invalid input. Please enter a sign followed by a number. ***\n" << endl;
					valid = false;
					break;

				} // end if

			} // end if

		} // end for loop

	} // end while loop

	// Set up LongInt structures

	op1 = new LongInt( sign1, operand1 );	// Operand 1
	op2 = new LongInt( sign2, operand2 );	// Operand 2
	quotient = new LongInt;					// Product

	// Call to division

	*quotient = op1->div( *op2 );			// Quotient = Operand1 / Operand2

	// Print result

	cout << "Result: (" << sign1 << ") " << operand1 << " / (" << sign2 << ") " << operand2 << " = (" << quotient->getSign() << ") " << quotient->getValue() << endl;

	// See if user wants to do more

	askForMore();
}

void power()
{
	char sign;						// Sign
	string value;					// String representation of value
	LongInt * valueLongInt;			// LongInt value
	unsigned long int exponent;		// Exponent
	LongInt * result;				// LongInt result

	char buffer[255];	// Buffer for value (input)

	// Fill array with default data

	for ( int i = 0; i < 255; i++ ) {

		buffer[i] = '\0';

	}

	bool valid = false;

	// Get value

	//while ( !valid ) {

	cout << "Input the operand to multiply by a POWER (e.g. +12345678): ";
	cin >> buffer;
	sign = buffer[0];

	for ( int i = 1; i <= 255; i++ ) {

		// Don't include null

		if ( buffer[i] != '\0' ) {

			// Must be a number

			if ( buffer[i] == '0' || buffer[i] == '1' || buffer[i] == '2' 
				|| buffer[i] == '3' || buffer[i] == '4' || buffer[i] == '5'
					|| buffer[i] == '6' || buffer[i] == '7' || buffer[i] == '8'
						|| buffer[i] == '9' ) {

				value = value + buffer[i];

				valid = true;

			} else {

				valid = false;

			} // end if

		} // end if

	} // end for loop

	//} // end while loop

	// Get second operand

	cout << "Input the exponent for POWER (No sign, e.g. 5): ";
	cin >> exponent;

	// Set up LongInt structures

	valueLongInt = new LongInt( sign, value );	// LongInt value
	result = new LongInt;						// LongInt result

	// Call to power

	*result = valueLongInt->pow( exponent );	// Result = value ^ exponent

	// Print result

	cout << "Result: " << valueLongInt->toString() << " ^ " << exponent << " = " << result->toString() << endl;

	// See if user wants to do more

	askForMore();
}

void givenData()
{

	cout << "\n*** Please be patient while we perform some very large calculations... ***\n" << endl;

	LongInt * a = new LongInt('+', "22222222");
	cout << "A = " << a->toString() << endl;

	LongInt * b = new LongInt('+', "55555555");
	cout << "B = " << b->toString() << endl;

	LongInt * c = new LongInt('+', "24681357");
	cout << "C = " << c->toString() << endl;

	LongInt * d = new LongInt('+', "18027036");
	cout << "D = " << d->toString() << endl;

	LongInt * e = new LongInt;
	cout << "E = A * D = ";
	*e = a->mult( *d );
	cout << e->toString() << endl;

	LongInt * f = new LongInt;
	cout << "F = A ^ 2 = ";
	*f = a->pow( 2 );
	cout << f->toString() << endl;

	LongInt * g = new LongInt;
	cout << "G = D ^ 2 = ";
	*g = d->pow( 2 );
	cout << g->toString() << endl;

	LongInt * h = new LongInt;
	cout << "H = B * C = ";
	*h = b->mult( *c );
	cout << h->toString() << endl;

	LongInt * i = new LongInt;
	cout << "I = A + D = ";
	*i = a->add( *d );
	cout << i->toString() << endl;

	LongInt * j = new LongInt;
	cout << "J = I ^ 2 = ";
	*j = i->pow( 2 );
	cout << j->toString() << endl;

	LongInt * k = new LongInt;
	cout << "K = J - F = ";
	*k = j->sub( *f );
	cout << k->toString() << endl;

	LongInt * l = new LongInt;
	cout << "L = K - G = ";
	*l = k->sub( *g );
	cout << l->toString() << endl;

	LongInt * m = new LongInt;
	cout << "M = L / E = ";
	*m = l->div( *e );
	cout << m->toString() << endl;
	
	delete f;
	delete g;
	delete i;
	delete j;
	delete k;
	delete l;
	delete m;

	LongInt * n = new LongInt;
	cout << "N = E ^ 5 = ";
	*n = e->pow( 5 );
	cout << n->toString() << endl;

	LongInt * o = new LongInt;
	cout << "O = H ^ 3 = ";
	*o = h->pow( 3 );
	cout << o->toString() << endl;

	LongInt * p = new LongInt;
	cout << "P = N - O = ";
	*p = n->sub( *o );
	cout << p->toString() << endl;

	LongInt * q = new LongInt;
	cout << "Q = N ^ 2 = ";
	*q = n->pow( 2 );
	cout << q->toString() << endl;

	LongInt * r = new LongInt;
	cout << "R = Q ^ 2 = ";
	*r = q->pow( 2 );
	cout << r->toString() << endl;

	LongInt * s = new LongInt;
	cout << "S = Q - R = ";
	*s = q->sub( *r );
	cout << s->toString() << endl;

	LongInt * t = new LongInt;
	cout << "T = S / P = ";
	*t = s->div( *p );
	cout << t->toString() << endl;

	LongInt * u = new LongInt;
	cout << "U = T - O = ";
	*u = t->sub( *o );
	cout << u->toString() << endl;

	LongInt * v = new LongInt;
	cout << "V = U - N = ";
	*v = u->sub( *n );
	cout << v->toString() << endl;

	LongInt * w = new LongInt;
	cout << "W = C ^ 2 = ";
	*w = c->pow( 2 );
	cout << w->toString() << endl;

	LongInt * x = new LongInt;
	cout << "X = B ^ 2 = ";
	*x = b->pow( 2 );
	cout << x->toString() << endl;

	LongInt * y = new LongInt;
	cout << "Y = W - X = ";
	*y = w->sub( *x );
	cout << y->toString() << endl;

	LongInt * z = new LongInt;
	cout << "Z = C + B = ";
	*z = c->add( *b );
	cout << z->toString() << endl;
	
	h = new LongInt;
	cout << "H = Y / Z = ";
	*h = y->div( *z );
	cout << h->toString() << endl;
	
	f = new LongInt;
	cout << "F = N ^ 5 = ";
	*f = n->pow( 5 );
	cout << f->toString() << endl;
	
	g = new LongInt;
	cout << "G = E ^ 25 = ";
	*g = e->pow( 25 );
	cout << g->toString() << endl;
	
	i = new LongInt;
	cout << "I = F / N = ";
	*i = f->div( *n );
	cout << i->toString() << endl;
	
	j = new LongInt;
	cout << "J = G / I = ";
	*j = g->div( *i );
	cout << j->toString() << endl;
	
	m = new LongInt;
	cout << "M = N ^ 10 = ";
	*m = n->pow( 10 );
	cout << m->toString() << endl;
	
	delete p;
	
	p = new LongInt;
	cout << "P = G ^ 2 = ";
	*p = g->pow( 2 );
	cout << p->toString() << endl;
	
	delete q;
	delete r;
	
	q = new LongInt;
	cout << "Q = P - M = ";
	*q = p->sub( *m );
	cout << q->toString() << endl;
	
	r = new LongInt;
	cout << "R = J - M = ";
	*r = j->sub( *m );
	cout << r->toString() << endl;
	
	delete q;
	delete r;
	
	// Delete the rest
	
	delete a;	delete b;	delete c;
	delete d;	delete e;	delete f;
	delete g;	delete h;	delete i;
	delete j;	delete m;	delete n;
	delete o;	delete p;	delete s;
	delete t;	delete u;	delete v;
	delete w;	delete x;	delete y;
	delete z;

	askForMore();

}

void exit()
{
	cout << "\nExiting..." << endl;
	exit(0);
}

void add()
{
	char sign1;			// Operand 1 sign
	char sign2;			// Operand 2 sign

	string operand1;	// String representation of operand 1
	string operand2;	// String representation of operand 2

	LongInt * op1;		// LongInt operand 1
	LongInt * op2;		// LongInt operand 2
	LongInt * sum;		// LongInt sum

	char value1[255];	// Buffer for 1st operand input
	char value2[255];	// Buffer for 2nd operand input

	// Fill arrays with default data

	for ( int i = 0; i < 255; i++ ) {

		value1[i] = '\0';
		value2[i] = '\0';

	}

	bool valid = false;

	// Get first operand

	while ( !valid ) {

		cout << "Input the first operand for ADD (e.g. +12345678): ";
		cin >> value1;
		sign1 = value1[0];

		for ( int i = 1; i <= 255; i++ ) {

			// Don't include null

			if ( value1[i] != '\0' ) {

				// Must be a number

				if ( value1[i] == '0' || value1[i] == '1' || value1[i] == '2' 
					|| value1[i] == '3' || value1[i] == '4' || value1[i] == '5'
						|| value1[i] == '6' || value1[i] == '7' || value1[i] == '8'
							|| value1[i] == '9' ) {

					operand1 = operand1 + value1[i];

					valid = true;

				} else {

					cout << "\n*** Error: Invalid input. Please enter a sign followed by a number. ***\n" << endl;
					valid = false;
					break;

				} // end if

			} // end if

		} // end for loop

	} // end while loop

	valid = false;	// Reset valid flag for second operand

	// Get second operand

	while ( !valid ) {

		cout << "Input the second operand for ADD (e.g. +12345678): ";
		cin >> value2;
		sign2 = value2[0];

		for ( int i = 1; i <= 255; i++ ) {

			// Don't include null

			if ( value2[i] != '\0' ) {

				// Must be a number

				if ( value2[i] == '0' || value2[i] == '1' || value2[i] == '2' 
					|| value2[i] == '3' || value2[i] == '4' || value2[i] == '5'
						|| value2[i] == '6' || value2[i] == '7' || value2[i] == '8'
							|| value2[i] == '9' ) {

					operand2 = operand2 + value2[i];

					valid = true;

				} else {

					cout << "\n*** Error: Invalid input. Please enter a sign followed by a number. ***\n" << endl;
					valid = false;
					break;

				} // end if

			} // end if

		} // end for loop

	} // end while loop

	// Set up LongInt structures

	op1 = new LongInt( sign1, operand1 );	// Operand 1
	op2 = new LongInt( sign2, operand2 );	// Operand 2
	sum = new LongInt;						// Sum

	// Call to addition

	*sum = op1->add( *op2 );				// Sum = Operand1 + Operand2

	// Print result

	cout << "Result: (" << sign1 << ") " << operand1 << " + (" << sign2 << ") " << operand2 << " = (" << sum->getSign() << ") " << sum->getValue() << endl;

	// See if user wants to do more

	askForMore();

}

void subtract()
{
	char sign1;			// Operand 1 sign
	char sign2;			// Operand 2 sign

	string operand1;	// String representation of operand 1
	string operand2;	// String representation of operand 2

	LongInt * op1;		// LongInt operand 1
	LongInt * op2;		// LongInt operand 2
	LongInt * sum;		// LongInt sum

	char value1[255];	// Buffer for 1st operand input
	char value2[255];	// Buffer for 2nd operand input

	// Fill arrays with default data

	for ( int i = 0; i < 255; i++ ) {

		value1[i] = '\0';
		value2[i] = '\0';

	}

	bool valid = false;

	// Get first operand

	while ( !valid ) {

		cout << "Input the first operand for SUBTRACT (e.g. +12345678): ";
		cin >> value1;
		sign1 = value1[0];

		for ( int i = 1; i <= 255; i++ ) {

			// Don't include null

			if ( value1[i] != '\0' ) {

				// Must be a number

				if ( value1[i] == '0' || value1[i] == '1' || value1[i] == '2' 
					|| value1[i] == '3' || value1[i] == '4' || value1[i] == '5'
						|| value1[i] == '6' || value1[i] == '7' || value1[i] == '8'
							|| value1[i] == '9' ) {

					operand1 = operand1 + value1[i];

					valid = true;

				} else {

					cout << "\n*** Error: Invalid input. Please enter a sign followed by a number. ***\n" << endl;
					valid = false;
					break;

				} // end if

			} // end if

		} // end for loop

	} // end while loop

	valid = false;	// Reset valid flag for second operand

	// Get second operand

	while ( !valid ) {

		cout << "Input the second operand for SUBTRACT (e.g. +12345678): ";
		cin >> value2;
		sign2 = value2[0];

		for ( int i = 1; i <= 255; i++ ) {

			// Don't include null

			if ( value2[i] != '\0' ) {

				// Must be a number

				if ( value2[i] == '0' || value2[i] == '1' || value2[i] == '2' 
					|| value2[i] == '3' || value2[i] == '4' || value2[i] == '5'
						|| value2[i] == '6' || value2[i] == '7' || value2[i] == '8'
							|| value2[i] == '9' ) {

					operand2 = operand2 + value2[i];

					valid = true;

				} else {

					cout << "\n*** Error: Invalid input. Please enter a sign followed by a number. ***\n" << endl;
					valid = false;
					break;

				} // end if

			} // end if

		} // end for loop

	} // end while loop

	// Set up LongInt structures

	op1 = new LongInt( sign1, operand1 );	// Operand 1
	op2 = new LongInt( sign2, operand2 );	// Operand 2
	sum = new LongInt;						// Sum

	// Call to addition

	*sum = op1->sub( *op2 );				// Sum = Operand1 - Operand2

	// Print result

	cout << "Result: (" << sign1 << ") " << operand1 << " - (" << sign2 << ") " << operand2 << " = (" << sum->getSign() << ") " << sum->getValue() << endl;

	// See if user wants to do more

	askForMore();

}

void askForMore()
{
	string answer;

	cout << "\nWould you like to perform another operation? (Y or N): ";
	cin >> answer;

	// User selected YES - get selection

	if ( answer == "Y" || answer == "y" || answer == "Yes" || answer == "yes" ) {

		getSelection();

	} 

	// User selected NO - exit

	else if ( answer == "N" || answer == "n" || answer == "No" || answer == "no" ){

		exit();

	} 

	// Invalid selection - ask again

	else {

		cout << "ERROR: Invalid response. Please try again." << endl;
		askForMore();

	}
}

void getSelection()
{
	cout << "LONG INTEGER ADT by KURTIS CHIAPPONE" << endl;
	cout << "CS-610 - November 20, 2008" << endl;
	cout << "\n-------------------------------------------------" << endl;
	cout << "Please choose an operation:" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "1. ADD" << endl;
	cout << "2. SUBTRACT" << endl;
	cout << "3. MULTIPLY" << endl;
	cout << "4. DIVIDE" << endl;
	cout << "5. POW" << endl;
	cout << "6. USING GIVEN DATA" << endl;
	cout << "7. EXIT" << endl;

	short int number;

	cout << "\nEnter Your Selection (1-7): ";
	cin >> number;

	switch ( number ) {

	case 1:
		add();
		break;

	case 2:
		subtract();
		break;

	case 3:
		multiply();
		break;

	case 4:
		divide();
		break;

	case 5:
		power();
		break;

	case 6:
		givenData();
		break;

	case 7:
		exit();
		break;

	default:
		cout << "ERROR: Invalid selection. Please try again." << endl;
		getSelection();
		break;

	}
}

int main()
{

	getSelection();
	
	return 0;
}
