

#include "LongInt.h"

LongInt::LongInt()
{	
	list = new DoublyLinkedList;
	max_digits = 4;	// Max digits per node
}

LongInt::LongInt( char _sign, string _value )
{	
	list = new DoublyLinkedList;
	sign = _sign;
	value = _value;
	max_digits = 4; // Max digits per node
	parse();
}

LongInt::~LongInt()
{
	list = NULL;
	delete list;
}

char LongInt::getSign()
{
	return sign;
}

long int LongInt::getOverflow( struct node * currentNode )
{
	long int overflow_digit = 0;

	overflow_digit = currentNode->data / 10000; // 100,000,000 for 8 digits

	if ( overflow_digit != 0 ) {

		currentNode->data = currentNode->data - ( overflow_digit * 10000 ); // 100,000,000 for 8 digits

	}

	return overflow_digit;
}

LongInt LongInt::add( LongInt _value )
{

	LongInt * operand1 = new LongInt( getSign(), getValue() );
	LongInt * operand2 = new LongInt( _value.getSign(), _value.getValue() );

	/**
	 * Special case where one of the operands
	 * is zero.
	 */

	if ( operand2->getValue() == "0" ) {

		return *operand1;

	} else if ( operand1->getValue() == "0" ) {

		return *operand2;

	}

	/**
	 * Signs of both operands are not equal, so we
	 * need to figure out which one is larger. We'll
	 * take the sign from the largest value and 
	 * subtract.
	 */

	if ( operand1->getSign() != operand2->getSign() ) {

		// Take sign of greater value

		int dat1 = operand1->getList().getFirst()->next->data;
		int dat2 = operand2->getList().getFirst()->next->data;

		int len1 = operand1->getList().getNumberOfDigits();
		int len2 = operand2->getList().getNumberOfDigits();

		// Length is the same, so compare first int

		if ( len1 == len2 ) {

			// Same number, so result is zero

			if ( dat1 == dat2 ) {

				LongInt * result = new LongInt('+', "0");
				return *result;

			}

			// Take first operand sign

			else if ( dat1 > dat2 ) {

				return sub( *operand1, *operand2 );

			} 

			// Take second operand sign

			else {

				return sub( *operand2, *operand1 );

			}

		}

		// First one is larger than second

		else if ( len1 > len2 ) {

			// Take first operand sign

			return sub( *operand1, *operand2 );

		}

		// Second one is larger than first

		else {

			// Make sign positive and subtract

			operand2->setSign('+');
			return sub( *operand2, *operand1 );

		}

	} 

	return add( *operand1, *operand2 );

}

LongInt LongInt::add( LongInt operand1, LongInt operand2 )
{

	LongInt * sum = new LongInt;
	sum->setSign( sign );

	struct node * n1, * n2, * rslt;
	long int partialSum, carry = 0;

	n1 = operand1.getList().getLast();
	n2 = operand2.getList().getLast();

	while ( n1->data >= 0 && n2->data >= 0 ) {

		partialSum = n1->data + n2->data + carry;	
		rslt = new struct node;
		rslt->data = partialSum;
		carry = getOverflow( rslt );
		sum->getList().addFirst( rslt->data );
		n1 = operand1.getList().getPrev( n1 );
		n2 = operand2.getList().getPrev( n2 );

	} // end while loop

	while ( n1->data >= 0 ) {

		partialSum = n1->data + carry;
		rslt = new struct node;
		rslt->data = partialSum;
		carry = getOverflow( rslt );
		sum->getList().addFirst( rslt->data );
		n1 = operand1.getList().getPrev( n1 );

	} // end while loop

	while ( n2->data >= 0 ) {

		partialSum = n2->data + carry;
		rslt = new struct node;
		rslt->data = partialSum;
		carry = getOverflow( rslt );
		sum->getList().addFirst( rslt->data );
		n2 = operand2.getList().getPrev( n2 );

	} // end while loop

	if ( carry > 0 ) {

		rslt = new struct node;
		rslt->data = carry;
		sum->getList().addFirst( rslt->data );

	} // end if

	/**
	 * Update string value of LongInt
	 */

	struct node * current = current = sum->getList().getFirst();
	struct node * tail = sum->getList().tail;

	string tostring;	// Final string value
	string buffer;		// String buffer

	// Iterate from first to last node

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

		stringstream out;
		out << data;
		buffer = out.str();

		// Append leading zeros, if any

		for ( int i = 0; i < zeros; i++ ) {

			buffer = "0" + buffer;

		}

		// Update final string

		tostring = tostring + buffer;

	}

	sum->setValue( tostring );	// Set value to new value
	
	/**
	 * Delete old pointers
	 */

	n1 = NULL;
	n2 = NULL;
	rslt = NULL;
	current = NULL;
	tail = NULL;
	
	delete n1;
	delete n2;
	delete rslt;
	delete current;
	delete tail;

	return *sum;
}

LongInt LongInt::sub( LongInt _value )
{

	LongInt * operand1 = new LongInt( getSign(), getValue() );
	LongInt * operand2 = new LongInt( _value.getSign(), _value.getValue() );

	/**
	 * Special case where one of the operands
	 * is zero.
	 */

	if ( operand2->getValue() == "0" || operand2->getValue() == "0000" ) {

		return *operand1;

	} else if ( operand1->getValue() == "0" || operand1->getValue() == "0000" ) {

		operand2->setSign('-');
		return *operand2;

	}

	/**
	 * Special case where the values are the
	 * same. Return zero.
	 */

	if ( operand1->getValue() == operand2->getValue() ) {

		LongInt * zero = new LongInt('+', "0");
		return *zero;

	}

	/**
	 * Signs of both operands are not equal, so we
	 * need to figure out which one is larger. We'll
	 * take the sign from the largest value and 
	 * subtract.
	 */

	if ( operand1->getSign() != operand2->getSign() ) {

		/**
		 * First sign is positive, but second sign
		 * is negative. We should change the sign
		 * of the second operand to positive and
		 * add instead.
		 * 
		 * e.g. (+)1 - (-)1 => (+)1 + (+)1
		 */

		if ( operand1->getSign() == '+' && operand2->getSign() == '-' ) {

			operand2->setSign('+');
			return add( *operand1, *operand2 );

		}

		/**
		 * First sign is negative and second sign
		 * is positive. Change the sign of the first
		 * operand to positive and add instead.
		 */

		if ( operand1->getSign() == '-' && operand2->getSign() == '+' ) {

			operand2->setSign('-');
			return add ( *operand1, *operand2 );

		}

		// Take sign of greater value

		int dat1 = operand1->getList().getFirst()->next->data;
		int dat2 = operand2->getList().getFirst()->next->data;

		int len1 = operand1->getList().getNumberOfDigits();
		int len2 = operand2->getList().getNumberOfDigits();

		// Length is the same, so compare first int

		if ( len1 == len2 ) {

			// Same number, so result is zero

			if ( dat1 == dat2 ) {

				LongInt * result = new LongInt('+', "0");
				return *result;

			}

			// Take first operand sign

			else if ( dat1 > dat2 ) {

				return sub( *operand1, *operand2 );

			} 

			// Take second operand sign

			else {

				return sub( *operand2, *operand1 );

			}

		}

		// First one is larger than second

		else if ( len1 > len2 ) {

			// Take first operand sign

			return sub( *operand1, *operand2 );

		}

		// Second one is larger than first

		else {

			// Take second operand sign

			return sub( *operand2, *operand1 );

		}

	} 

	/**
	 * Signs are positive. Figure out which
	 * has the largest value.
	 */

	if ( operand1->getSign() == '+' && operand2->getSign() == '+' ) {

		// Take sign of greater value

		int dat1 = operand1->getList().getFirst()->next->data;
		int dat2 = operand2->getList().getFirst()->next->data;

		int len1 = operand1->getList().getNumberOfDigits();
		int len2 = operand2->getList().getNumberOfDigits();

		// Length is the same, so compare first int

		if ( len1 == len2 ) {

			if ( dat1 == dat2 ) {

				return sub( *operand1, *operand2 );

			}

			// Take first operand sign

			else if ( dat1 > dat2 ) {

				operand2->setSign('-');
				return sub( *operand1, *operand2 );

			} 

			// Take second operand sign

			else {

				LongInt result = sub( *operand2, *operand1 );
				result.setSign('-');
				return result;

			}

		}

		// First one is larger than second

		else if ( len1 > len2 ) {

			// Take first operand sign

			return sub( *operand1, *operand2 );

		}

		// Second one is larger than first

		else {

			LongInt result = sub( *operand2, *operand1 );
			result.setSign('-');
			return result;

		}

	}

	/**
	 * Signs are negative. Figure out which
	 * has the largest value.
	 */

	if ( operand1->getSign() == '-' && operand2->getSign() == '-' ) {

		// Take sign of greater value

		int dat1 = operand1->getList().getFirst()->next->data;
		int dat2 = operand2->getList().getFirst()->next->data;

		int len1 = operand1->getList().getNumberOfDigits();
		int len2 = operand2->getList().getNumberOfDigits();

		// Length is the same, so compare first int

		if ( len1 == len2 ) {

			// Same number, so result is zero

			if ( dat1 == dat2 ) {

				LongInt * result = new LongInt('+', "0");
				return *result;

			}

			// Take first operand sign

			else if ( dat1 > dat2 ) {

				operand2->setSign('+');
				return sub( *operand1, *operand2 );

			} 

			// Take second operand sign

			else {

				operand2->setSign('+');
				return sub( *operand2, *operand1 );

			}

		}

		// First one is larger than second

		else if ( len1 > len2 ) {

			// Take first operand sign

			return sub( *operand1, *operand2 );

		}

		// Second one is larger than first

		else {

			operand2->setSign('+');
			return sub( *operand2, *operand1 );

		}

	}	

	return sub( *operand1, *operand2 );

}

LongInt LongInt::sub( LongInt operand1, LongInt operand2 )
{

	vector <LongInt> v;								// Vector to hold partial values
	struct node * n1, * n2, * rslt;					// Nodes N1, N2, result
	long int sum, carry = 0;						// Actual sum and carry
	LongInt * partialSum;							// LongInt to store partial sum

	/**
	 * Initialize nodes. Both nodes start
	 * at the rightmost digit in the value.
	 */

	n1 = operand1.getList().getLast();				// Start N1 at rightmost digit
	n2 = operand2.getList().getLast();				// Start N2 at rightmost digit

	/**
	 * While both nodes have data...
	 */

	while ( n1->data >= 0 && n2->data >= 0 ) {

		partialSum = new LongInt;	// Initialize partial LongInt
		partialSum->setSign('+'); 	// Assume positive sign for now

		/**
		 * Special Case:
		 * If N1 < N2, we need to subtract 1 from N1's previous
		 * node and add to N2 (i.e., "borrow"). Else we simply
		 * subtract.
		 */

		struct node * prevNode = new struct node;
		prevNode = n1->prev;

		if ( n1->data < n2->data ) {

			while( n1->data < n2->data ) {

				if ( prevNode->data == 0 ) {

					n1->data = n1->data + 10000;

					while ( prevNode->data == 0 ) {

						prevNode->data = 9999;
						prevNode = operand1.getList().getPrev( prevNode );	

					}

					if ( prevNode->data > 0 ) {

						prevNode->data = prevNode->data - 1;

					}

				} else if ( prevNode->data > 0 ) {

					n1->data = n1->data + 10000;
					prevNode->data = prevNode->data - 1;

					/**
					 * If this node's data is zero, check
					 * if there is a previous node. If the
					 * node before this one is the head,
					 * we want to discard this "empty"
					 * node.
					 */

					if ( prevNode->data == 0 ) {

						// Check if the previous node is the head

						if ( prevNode->prev->data < 0 ) {

							// Remove this node since it is empty
							// and there is no node before it.
							// This should be node #1.

							operand1.getList().remove( 1 );

						}

					}

				}

			} // end while

			struct node * temp = new struct node;
			sum = n1->data - n2->data;	
			temp->data = sum;
			getOverflow( temp );

			/**
			 * Update the sum
			 */

			n2->data = temp->data;
			sum = temp->data;

		}

		/**
		 * Simply subtract
		 */

		else {

			sum = n1->data - n2->data;

		}

		/**
		 * If the sum is less than zero (i.e. negative),
		 * let's multiply by -1 to make the integer
		 * positive, because we store the sign outside
		 * of the actual integer.
		 */

		if ( sum < 0 ) {

			sum = sum * -1; 		 	// Make positive
			partialSum->setSign('-');	// Set sign to negative

		}

		/**
		 * If there exists a node to the right (in N1 or N2), we
		 * have to append zeros to this sum.
		 */

		struct node * temp1 = operand1.getList().getNext( n1 );
		struct node * temp2 = operand2.getList().getNext( n2 );
		string s;

		if ( temp1->data >= 0 || temp2->data >= 0 ) {

			int count = 0;	// Number of nodes to the right

			// Check N1

			while ( temp1->data >= 0 ) {

				count = count + 1;								// Increment count
				temp1 = operand1.getList().getNext( temp1 );	// Move to next node

			}

			// Put sum in string

			ostringstream osum;
			osum << sum;
			s = osum.str();

			/**
			 * According to max_digits, append max_digits
			 * zeros for every node to the right of this
			 * node.
			 */

			for ( int j = 0; j < max_digits; j++ ) {	// Max digits

				for ( int i = 0; i < count; i++ ) {		// Number of nodes

					s = s + "0";

				}

			}

			partialSum->setValue( s ); // Update the value of the product

		} else {

			/**
			 * Otherwise, simply add the data
			 * to the list.
			 */

			rslt = new struct node;							// New Result Node
			rslt->data = sum;								// Add result to node
			carry = getOverflow( rslt );					// Calculate overflow
			partialSum->getList().addFirst( rslt->data );	// Add data

			/**
			 * If there is a carry, add it to
			 * the first node.
			 */

			if ( carry > 0 ) {

				partialSum->getList().addFirst( carry );

			}

		} // end if

		// Update string value

		struct node * current = current = partialSum->getList().getFirst();
		struct node * tail = partialSum->getList().tail;

		string buffer = "";
		string tostring = "";

		/**
		 * Now we have to add on any leading
		 * zeros which have been truncated.
		 */

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

			stringstream out;
			out << data;
			buffer = out.str();

			// Append leading zeros, if any

			for ( int i = 0; i < zeros; i++ ) {

				buffer = "0" + buffer;

			}

			// Update final string

			tostring = tostring + buffer;

		} // end while loop

		partialSum->setValue( tostring );				// Set value to new value	
		v.push_back( *partialSum ); 					// Insert into vector

		// Move to previous nodes

		n1 = operand1.getList().getPrev( n1 );
		n2 = operand2.getList().getPrev( n2 );

	} // end while loop

	/**
	 * This handles the case where N1 still has data
	 * but N2 is already finished. In this case, we 
	 * simply bring the number down and append any
	 * zeros if there is a node to the right of it.
	 * 
	 * e.g.  +55551111  <-- N1
	 *     - +    1111  <-- N2
	 *     -----------
	 *       +55550000  <-- Rest of N1 is brought down (5555)
	 */

	while ( n1->data >= 0 ) {

		partialSum = new LongInt;	// Initialize partial LongInt
		partialSum->setSign('+'); 	// This is positive
		sum = n1->data;				// Sum; we actually just bring the number down since N2 is empty

		/**
		 * If there exists a node to the right (in N1), we
		 * have to append zeros to this sum.
		 */

		struct node * temp1 = operand1.getList().getNext( n1 );
		string s;

		if ( temp1->data >= 0 ) {

			int count = 0;	// Number of nodes to the right

			// Check N1

			while ( temp1->data >= 0 ) {

				count = count + 1;								// Increment count
				temp1 = operand1.getList().getNext( temp1 );	// Move to next node

			}

			// Put sum in string

			ostringstream osum;
			osum << sum;
			s = osum.str();

			/**
			 * According to max_digits, append max_digits
			 * zeros for every node to the right of this
			 * node.
			 */

			for ( int j = 0; j < max_digits; j++ ) {	// Max digits

				for ( int i = 0; i < count; i++ ) {		// Number of nodes

					s = s + "0";

				}

			}

			partialSum->setValue( s ); // Update the value of the product

		} else {

			/**
			 * Otherwise, simply add the data
			 * to the list.
			 */

			rslt = new struct node;							// New Result Node
			rslt->data = sum;								// Add result to node
			carry = getOverflow( rslt );					// Calculate overflow
			partialSum->getList().addFirst( rslt->data );	// Add data

			/**
			 * If there is a carry, add it to
			 * the first node.
			 */

			if ( carry > 0 ) {

				partialSum->getList().addFirst( carry );

			}

		} // end if

		// Update string value

		struct node * current = current = partialSum->getList().getFirst();
		struct node * tail = partialSum->getList().tail;

		string buffer = "";
		string tostring = "";

		/**
		 * Now we have to add on any leading
		 * zeros which have been truncated.
		 */

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

			stringstream out;
			out << data;
			buffer = out.str();

			// Append leading zeros, if any

			for ( int i = 0; i < zeros; i++ ) {

				buffer = "0" + buffer;

			}

			// Update final string

			tostring = tostring + buffer;

		} // end while loop

		partialSum->setValue( tostring );				// Set value to new value	
		v.push_back( *partialSum ); 					// Insert into vector

		// Move to previous node

		n1 = operand1.getList().getPrev( n1 );

	} // end while loop

	/**
	 * Add up elements in the vector
	 */

	vector<LongInt>::iterator itVectorData;

	LongInt * final = new LongInt('+', "0");

	for( itVectorData = v.begin(); itVectorData != v.end(); itVectorData++ ) {

		LongInt *temp = new LongInt;	// New LongInt to store operand 1
		*temp = *(itVectorData);		// Get value from iterator

		// Perform addition

		LongInt * operand1 = new LongInt( temp->getSign(), temp->getValue() );

		//cout << " *** " << final->toString() << " + " << operand1->toString() << " = ";

		if ( operand1->getSign() == '-' ) {

			*final = final->add( *operand1 );

		} 

		else if ( final->getSign() == '-' ) {

			*final = final->add( *operand1, *final );

		}

		else {

			*final = final->add( *operand1 );

		}

		//cout << final->toString() << endl;

	}

	//cout << "Final: " << final->toString() << endl;

	/**
	 * Delete old pointers
	 */
	
	n1 = NULL;
	n2 = NULL;
	rslt = NULL;
	partialSum = NULL;
	
	delete n1;
	delete n2;
	delete rslt;
	delete partialSum;

	return *final;
}

LongInt LongInt::mult( LongInt _value )
{

	LongInt * operand1 = new LongInt( getSign(), getValue() );
	LongInt * operand2 = new LongInt( _value.getSign(), _value.getValue() );

	/**
	 * Eliminate the special case where either
	 * of the values is zero. Simply return zero.
	 * 
	 * e.g. x * 0 = 0
	 *      0 * x = 0
	 */

	if ( operand2->getValue() == "0" || operand1->getValue() == "0" ) {

		return LongInt('+', "0");

	}

	/**
	 * NOTE: Since the sign does not change the
	 * product value, we assume for now that the
	 * sign is positive and check the sign at
	 * the end before the return.
	 */

	vector <LongInt> v;								// Vector to hold multiplied values
	struct node * n1, * n2, * rslt;					// Nodes N1, N2, result
	long int partialProduct, carry = 0;				// Actual product and carry
	LongInt * product;								// LongInt to store this product

	/**
	 * Initialize nodes. Both nodes start
	 * at the rightmost digit in the value.
	 */

	n1 = operand1->getList().getLast();				// Start N1 at rightmost digit
	n2 = operand2->getList().getLast();				// Start N2 at rightmost digit

	/**
	 * ---------------------------------
	 * While both nodes have data >= 0:
	 * ---------------------------------
	 * - N1 * N2 = partial product
	 * - Move N1 left
	 * - If N1 has no more data but N2 does,
	 *   reset N1 to last node and move N2
	 *   left.
	 * - Iterate
	 * - Complete when N1 and N2 do not have
	 *   data.
	 */

	while ( n1->data >= 0 && n2->data >= 0 ) {

		partialProduct = 0;							// Product
		carry = 0;									// Carry
		product = new LongInt;						// Initialize LongInt
		product->setSign('+'); 						// Assuming positive sign (for now)
		partialProduct = ( n1->data * n2->data );	// Multiply
		rslt = new struct node;						// Create new node
		string p;									// String to hold product

		/**
		 * If there exists a node to the right (in N1 or N2), we
		 * have to append zeros to this product.
		 */

		struct node * temp1 = operand2->getList().getNext( n2 );
		struct node * temp2 = operand1->getList().getNext( n1 );

		if ( temp1->data >= 0 || temp2->data >= 0 ) {

			int count = 0;	// Number of nodes to the right

			// Check N1

			while ( temp1->data >= 0 ) {

				count = count + 1;								// Increment count
				temp1 = operand2->getList().getNext( temp1 );	// Move to next node

			}

			// Check N2

			while ( temp2->data >= 0 ) {

				count = count + 1;								// Increment count
				temp2 = operand1->getList().getNext( temp2 );	// Move to next node

			}

			// Put product in string

			ostringstream prod;
			prod << partialProduct;
			p = prod.str();

			/**
			 * According to max_digits, append max_digits
			 * zeros for every node to the right of this
			 * node.
			 */

			for ( int j = 0; j < max_digits; j++ ) {	// Max digits

				for ( int i = 0; i < count; i++ ) {		// Number of nodes

					p = p + "0";

				}

			}

			product->setValue( p ); // Update the value of the product

		} else {

			/**
			 * Otherwise, simply add the data
			 * to the list.
			 */

			rslt->data = partialProduct;				// Add result to node	
			carry = getOverflow( rslt );				// Calculate carry
			product->getList().addFirst( rslt->data );	// Add data

			/**
			 * If there is a carry, add it to
			 * the first node.
			 */

			if ( carry > 0 ) {

				product->getList().addFirst( carry );

			}

		}

		// Update string value

		struct node * current = current = product->getList().getFirst();
		struct node * tail = product->getList().tail;

		string buffer = "";
		string tostring = "";

		/**
		 * Now we have to add on any leading
		 * zeros which have been truncated.
		 */

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

			stringstream out;
			out << data;
			buffer = out.str();

			// Append leading zeros, if any

			for ( int i = 0; i < zeros; i++ ) {

				buffer = "0" + buffer;

			}

			// Update final string

			tostring = tostring + buffer;

		}

		product->setValue( tostring );				// Set value to new value
		v.push_back( *product ); 					// Insert into vector

		/**
		 * Multiplication for this number has
		 * ended. Iterate.
		 */

		n1 = list->getPrev( n1 );	// Move N1 left

		/**
		 * If N1 has no more data but N2 has a previous
		 * node that has yet to be multiplied, reset
		 * N1 to the last node and move N2 left.
		 */

		if ( n1->data < 0 && n2->prev->data >= 0 ) {

			n1 = list->getLast();					// N1 is now the last node
			n2 = _value.getList().getPrev( n2 );	// N2 is the node prior to this one

		}

	} // end while loop

	/**
	 * Add up elements in the vector
	 */

	vector<LongInt>::iterator itVectorData;

	LongInt * final = new LongInt('+', "0");

	for( itVectorData = v.begin(); itVectorData != v.end(); itVectorData++ ) {

		LongInt *temp = new LongInt;	// New LongInt to store operand 1
		*temp = *(itVectorData);		// Get value from iterator

		// Perform addition

		LongInt * partialResult = new LongInt( temp->getSign(), temp->getValue() );
		*final = final->add( *partialResult );

	}

	/**
	 * Delete elements in vector
	 */

	for( itVectorData = v.begin(); itVectorData != v.end(); itVectorData++ ) {

		LongInt *temp = new LongInt;	// New LongInt to store operand 1
		*temp = *(itVectorData);		// Get value from iterator

		delete temp;

	}

	/**
	 * Check sign
	 */

	char sign1 = operand1->getSign();	// Operand 1 Sign
	char sign2 = operand2->getSign();	// Operand 2 Sign

	// Both signs are the same

	if ( sign1 == sign2 ) {

		/**
		 * If signs are both negative, we have to
		 * make them positive. Else if the signs
		 * are both positive, the sign stays the
		 * same.
		 * 
		 * e.g. +1 * +1 = +1
		 *      -1 * -1 = +1
		 */

		final->setSign('+');

	}

	// Signs are not the same

	else if ( sign1 != sign2 ) {

		/**
		 * If the signs aren't equal, then
		 * one must be positive and one must
		 * be negative. Either way, the sign
		 * will become negative.
		 * 
		 * e.g. +1 * -1 = -1
		 *      -1 * +1 = -1
		 */

		final->setSign('-');

	}
	
	/**
	 * Delete old pointers
	 */

	operand1 = NULL;
	operand2 = NULL;
	
	delete operand1;
	delete operand2;

	return *final;

}

LongInt LongInt::div( LongInt _value )
{

	LongInt * dividend = new LongInt( getSign(), getValue() );
	LongInt * divisor = new LongInt( _value.getSign(), _value.getValue() );
	LongInt * quotient = new LongInt('+', "0");
	bool isNegative = false;

	/**
	 * If both signs are the same, the quotient will
	 * be positive.
	 */

	if ( dividend->getSign() == divisor->getSign() ) {

		isNegative = false;

	}

	/**
	 * If either signs are negative, the 
	 * quotient will be negative.
	 */

	else if ( dividend->getSign() == '-' || divisor->getSign() == '-' ) {

		isNegative = true;
		dividend->setSign('+');
		divisor->setSign('+');

	}

	/**
	 * Special case where the divisor is zero. This is
	 * technically `undefined` but we will return
	 * zero.
	 */

	if ( divisor->getValue() == "0" || divisor->getValue() == "0000" ) {

		return *quotient;

	}

	/**
	 * Special case where the divisor is one. We will
	 * return the dividend back.
	 */

	if ( divisor->getValue() == "1" || divisor->getValue() == "0001" ) {


		if ( isNegative ) quotient->setSign('-');
		else quotient->setSign('+');

		quotient->setValue( dividend->getValue() );
		return *quotient;

	}

	/**
	 * If value of the dividend is equal to the
	 * value of the divisor, the quotient is 1.
	 */

	if ( divisor->getValue() == dividend->getValue() ) {

		if ( isNegative ) quotient->setSign('-');
		else quotient->setSign('+');

		quotient->setValue( dividend->getValue() );
		return *quotient;

	}

	/**
	 * If the divisor is larger than the dividend,
	 * the quotient will be <= 0, so we will return
	 * zero (since we are not using decimals).
	 */

	if ( divisor->isGreaterThan( *dividend ) ) {

		quotient->setValue("0");
		quotient->setSign('+');
		return *quotient;

	}

	/**
	 * Begin division
	 */

	//cout << "Operation:\t" << dividend->toString() << " / " << divisor->toString() << endl;

	while ( !_value.isGreaterThan( *divisor ) ) {

		/**
		 * Make sure the dividend is not
		 * zero or less.
		 */

		long int div = dividend->getList().getFirst()->next->data;
		if ( div == 0 || div < 0 ) break;

		int len1 = dividend->getList().getNumberOfDigits();	// Length of Dividend
		int len2 = _value.getList().getNumberOfDigits();	// Length of Divisor
		int offset = len1 - len2;							// Offset

		//cout << "Offset:\t" << len1 << " - " << len2 << " = " << offset << endl;
		//cout << "Divisor: " << divisor->toString() << " Dividend: " << dividend->toString() << endl;

		/**
		 * Add zeros to the divisor
		 */

		string multiple = "1";					// Set multiple to 1 initially (we add 0's after)
		string buffer = _value.getValue();		// Set buffer to divisor value

		for ( int i = 0; i < offset; i++ ) {

			buffer = buffer + "0";				// Add zeros to buffer (divisor)
			multiple = multiple + "0";			// Add zeros to multiple (power of 10)

		}

		divisor->setValue( buffer );			// Update the divisor value

		//cout << "Multiple:\t" << multiple << endl;

		/**
		 * Make sure divisor is not larger
		 * than the dividend
		 */

		if ( divisor->isGreaterThan( *dividend ) ) {

			buffer = buffer.substr( 0, buffer.size() - 1 );			// Minus one zero from buffer
			multiple = multiple.substr( 0, multiple.size() - 1 );	// Minus one zero from multiple
			divisor->setValue( buffer );							// Update divisor value

		}

		//cout << "Multiple:\t" << multiple << endl;
		//cout << "Divisor:\t" << divisor->toString() << endl;

		*dividend = dividend->sub( *divisor );

		//cout << "Current Dividend: " << dividend->toString() << endl;

		LongInt * m = new LongInt('+', multiple);
		*quotient = quotient->add( *m );

		//cout << "Current Quotient: " << quotient->toString() << endl;
		//cout << endl;

		m = NULL;
		delete m;

	}

	dividend = NULL;
	divisor = NULL;
	
	delete dividend;
	delete divisor;

	/**
	 * Check sign of quotient
	 */

	if ( isNegative ) quotient->setSign('-');
	else quotient->setSign('+');

	return *quotient;

}

bool LongInt::isGreaterThan( LongInt _value )
{

	/**
	 * First check by length of digits
	 */

	// Length is greater than

	if ( getList().getNumberOfDigits() > _value.getList().getNumberOfDigits()  ) {

		return true;

	}

	// Length is less than

	else if ( getList().getNumberOfDigits() < _value.getList().getNumberOfDigits() ) {

		return false;

	}

	// Length is equal, so we much check node-by-node

	else if ( getList().getNumberOfDigits() == _value.getList().getNumberOfDigits() ) {

		struct node * currFirst = new struct node;
		struct node * currSecond = new struct node;

		currFirst = getList().getFirst()->next;
		currSecond = _value.getList().getFirst()->next;

		// Compare first data to second data

		while ( currFirst->data >= 0 && currSecond->data >= 0 ) { // We stop at the tail

			// First data > Second data

			if ( currFirst->data > currSecond->data ) {

				return true;

			}

			// First data < Second data

			else if ( currFirst->data < currSecond->data ) { 

				return false;

			}

			// Equal -- move to next nodes

			else {

				currFirst = getList().getNext( currFirst );
				currSecond = _value.getList().getNext( currSecond );

			}

		}

	}

	return false;

}

LongInt LongInt::pow( unsigned long int exponent )
{

	/**
	 * Special case where the exponent is zero.
	 * We will return 1.
	 */

	if ( exponent == 0 ) {

		LongInt * one = new LongInt('+', "1");
		return *one;

	}

	/**
	 * Special case where the exponent is one.
	 * We will return the number itself.
	 * 
	 * e.g.	12345678 ^ 1 = 12345678
	 */

	if ( exponent == 1 ) {

		return *this;

	}

	/**
	 * Begin power function
	 */

	LongInt * operand = new LongInt( getSign(), getValue() );
	LongInt * result = new LongInt('+', "1");

	while ( exponent ) {

		if ( exponent & 1 ) {

			*result = result->mult( *operand );

			if ( exponent == 1 ) break;
			
		}

		*operand = operand->mult( *operand );
		exponent = exponent / 2;

	}

	operand = NULL;
	delete operand;

	return *result;

}

DoublyLinkedList LongInt::getList()
{
	return *list;
}

string LongInt::getValue()
{
	return value;
}

void LongInt::setSign( char _sign )
{
	sign = _sign;
}

void LongInt::setValue( string _value )
{
	value = _value;
	parse();
}

void LongInt::normalize()
{

	struct node * current = new struct node;
	current = getList().getFirst()->next;

	while ( current->data == 0 ) {

		getList().remove(1);
		current = getList().getNext( current );

	}

	string value;
	current = getList().getFirst()->next;

	while ( current->data >= 0 ) {

		ostringstream o;
		o << current->data;
		value = value + o.str();
		current = getList().getNext( current );

	}

	setValue( value );

	if ( value == "" ) {

		setValue("0");

	}

}

void LongInt::parse()
{

	list->empty();	// Empty the list

	char ch[ value.length() + 1 ];	// Char array to store string
	strcpy( ch, value.c_str() );	// Copy the string into the char array

	// Length of string, taking into consideration NULL terminating char (-1 from length)
	int len = ( sizeof( ch ) / sizeof( char ) ) - 1;

	// Update number of digits counter
	list->setNumberOfDigits( len );

	// Count to keep track of max limit of int
	int count = 0;

	// Temporary string to hold the current "set" of ints
	string temp = "";

	for ( int i = len - 1; i  >= 0; i-- ) {

		// Check if this is the max_digit index

		if ( count > 0 && count % max_digits == 0 ) {

			// Add string temp to list
			long int intReturn = atoi( temp.c_str() );	// Convert to int
			list->addFirst( intReturn );				// Add to beginning of list
			temp = "";									// Reset string

		}

		temp = ch[i] + temp;	// Add char to string temp
		count++;				// Increment count

	} // end for loop

	// Add remaining numbers to list
	long int intReturn = atoi( temp.c_str() );	// Convert to int
	list->addFirst( intReturn );				// Add to beginning of list

}

void LongInt::print()
{
	cout << toString() << endl;
}

string LongInt::toString()
{
	return sign + value;
}
