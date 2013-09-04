
struct node {

	long int data;
	int length;
	int leadingZeros;
	struct node * prev;
	struct node * next;

	node() {

		data = 0;
		prev = 0;
		next = 0;
		length = 0;
		leadingZeros = 0;

	}

};
