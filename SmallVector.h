/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 30.03.2017
 */

#include <cstring> // memcpy

#define ST_SIZE 32 // Static buffer size

class SmallVector {
	int static_buffer[ST_SIZE];
	int *dynamic_buffer;
	int size;
	int capacity;
	void shrink(int amount);
	void expand(int amount);
 public:
	SmallVector();
	SmallVector(const int *source, int construct_size); 
	SmallVector(const SmallVector &source);
	SmallVector(const SmallVector &source, int construct_size);
	~SmallVector();
	void push_back(int push);
	void push_back(int *push, int push_size);
	int pop_back();
	const SmallVector reverse() const;
	SmallVector operator+(const SmallVector &operand) const;
	SmallVector operator*(int replicate) const;
	int& operator[](int i);
	const int& operator[](int i) const;
	const SmallVector& operator=(const SmallVector &assignment);
	const int getSize() const;
	const int getCapacity() const;
};

SmallVector::SmallVector() {
	// Default constructor constructs empty SmallVector
	for(int i = 0; i < ST_SIZE; i++) {
		static_buffer[i] = 0;
	}
	
	size = 0;
	capacity = ST_SIZE;
}

SmallVector::SmallVector(const int *source, int construct_size) {
	// Allocate memory for dynamic buffer if needed
	if (construct_size > ST_SIZE) 
		dynamic_buffer = new int[construct_size-ST_SIZE];
	
	// Copy number of |construct_size| elements from |source| to |this| 
	for(int i = 0; i < construct_size; i++) {
		if (i >= ST_SIZE) {
			*(dynamic_buffer+(i-ST_SIZE)) = *(source+i);
		}
		else {
			*(static_buffer+i) = *(source+i);
		}
	}
	
	size = construct_size;
	
	// Determine capacity regarding if dynamic buffer is allocated or not
	if(construct_size > ST_SIZE)
		capacity = construct_size;
	else
		capacity = ST_SIZE;
}

SmallVector::SmallVector(const SmallVector &source) {
	int construct_size = source.getCapacity();
	
	// Allocate memory for dynamic buffer if needed
	if (construct_size > ST_SIZE) 
		dynamic_buffer = new int[construct_size-ST_SIZE];
	
	// Copy |source| to |this|
	memcpy(this, &source, sizeof(source));	
}

SmallVector::SmallVector(const SmallVector &source, int construct_size) {
	// Allocate memory for dynamic buffer if needed
	if (construct_size > ST_SIZE) 
		dynamic_buffer = new int[construct_size-ST_SIZE];
	
	// Copy number of |construct_size| elements from |source| to |this| 
	for(int i = 0; i < construct_size; i++) {
		if (i >= ST_SIZE) {
			*(dynamic_buffer+(i-ST_SIZE)) = *((source.dynamic_buffer)+(i-ST_SIZE));
		}
		else {
			*(static_buffer+i) =  *(source.static_buffer+i);
		}
	}
	
	size = construct_size;
	
	// Determine capacity regarding if dynamic buffer is allocated or not
	if(construct_size > ST_SIZE)
		capacity = construct_size;
	else
		capacity = ST_SIZE;	
}

SmallVector::~SmallVector() {
	// Destroy the dynamic buffer if there is one
	if (capacity > ST_SIZE)
		delete [] dynamic_buffer;
}

void SmallVector::shrink(int amount) {
	// If the elements in the SmallVector cannot fit if SmallVector 
	// is shrinked, do not do any operations
	if (capacity-amount < size || size == ST_SIZE)
		return;
	// Back up the elements in the SmallVector before destroying
	int *temp = new int[capacity-ST_SIZE];
	memcpy(temp, dynamic_buffer, capacity-ST_SIZE);
	delete [] dynamic_buffer;
	// Reallocate with new space and give the backed up elements back
	dynamic_buffer = new int[capacity-ST_SIZE-amount];
	memcpy(dynamic_buffer, temp, capacity-ST_SIZE);
	delete [] temp;
	capacity -= amount;
}

void SmallVector::expand(int amount) {
	// If dynamic memory is allocated do the operations for it
	if (capacity != ST_SIZE) {
		// Back up the elements in the SmallVector before destroying
		int *temp = new int[capacity-ST_SIZE];
		memcpy(temp, dynamic_buffer, sizeof(int)*(capacity-ST_SIZE));
		delete [] dynamic_buffer;
		// Reallocate with new space and give the backed up elements back
		dynamic_buffer = new int[capacity-ST_SIZE+amount];
		memcpy(dynamic_buffer, temp, sizeof(int)*(capacity-ST_SIZE));
		delete [] temp;
	}
	else
		dynamic_buffer = new int[amount];
		
	capacity += amount;
}

void SmallVector::push_back(int push) {
	// If there is space for pushing in the static buffer, push there
	if (size < ST_SIZE) 
		static_buffer[size] = push;
	else {
		// If there is not enough space for pushing, expand the SmallVector
		if(capacity < size+1) 
			expand(1);	
		*(dynamic_buffer+(size-ST_SIZE)) = push;
	}
	size++;
}

void SmallVector::push_back(int *push, int push_size) {
	// If there is not enough space for pushing, expand the SmallVector
	if (capacity < size+push_size) 
		expand(size+push_size-capacity);
	
	// Push all the elements in |push| to the end of the SmallVector
	for(int i = size, j = 0; j < push_size; i++, j++) {
		if(i < ST_SIZE)
			static_buffer[i] = *(push+j);
		else 
			*(dynamic_buffer+(i-ST_SIZE)) = *(push+j);
	}   
	// Increase size by amount of the pushed elements
	size += push_size;
}

int SmallVector::pop_back() {
	int temp;
	// Pop the last element of the SmallVector from where it is stored
	if (size <= ST_SIZE) {
		temp = static_buffer[size-1];
		static_buffer[size-1] = 0;
	}
	else {
		temp = *(dynamic_buffer+(size-ST_SIZE-1));
		*(dynamic_buffer+(size-ST_SIZE-1)) = 0;
	}
	// Decrement size and return popped element
	size--;
	return temp;
}

const SmallVector SmallVector::reverse() const {
	int temp[size];
	// Store elements of |this| to |temp| beginning from end 
	for(int i = size-1, j=0; i >= 0; i--, j++) {
		if (j < ST_SIZE)
			temp[i] = static_buffer[j];
		else 
			temp[i] = *(dynamic_buffer+(j-ST_SIZE));
	}
	return SmallVector(temp, size);
}

SmallVector SmallVector::operator+(const SmallVector &operand) const {
	int temp[size+operand.getSize()];
	// Store the elements of |this| to |temp|
	for(int i = 0, j=0; j < size; i++, j++) {
		if (j < ST_SIZE)
			temp[i] = static_buffer[j];
		else 
			temp[i] = *(dynamic_buffer+(j-ST_SIZE));
	}
	// Store the elements of |operand| to |temp| beginning from the end
	for(int i=size, j=0; j < operand.getSize(); i++, j++) {
		if (j < ST_SIZE)
			temp[i] = operand.static_buffer[j];
		else 
			temp[i] = *(operand.dynamic_buffer+(j-ST_SIZE));
	}	
	// Return concatenated SmallVector
	return SmallVector(temp, size+operand.getSize());
}

SmallVector SmallVector::operator*(int replicate) const {
	int temp[size*replicate];
	// Replicate elements for |replicate| times and store in |temp| 
	for(int i = 0, k = 0; k < replicate; k++) {
		// Assign all elements in the SmallVector to |temp|
		for(int j=0; j < size; j++, i++) {
			if (j < ST_SIZE)
				temp[i] = static_buffer[j];
			else 
				temp[i] = *(dynamic_buffer+(j-ST_SIZE));
		}
	}	
	return SmallVector(temp, size*replicate);
}

int& SmallVector::operator[](int i) {
	// If index is a negative number, then increase by |size| to 
	// begin from the first element of the SmallVector
	if (i < 0)
		i += size;
	
	if (i >= 0 && i < ST_SIZE) {
		if (i < size)
			return static_buffer[i];
		// If index exceeds size of the vector, return last element
		else 
			return static_buffer[size-1];
	}
	// If index exceeds static buffer
	else if (i >= 0 && i >= ST_SIZE) {
		if (i < size)
			return *(dynamic_buffer+(i-ST_SIZE));
		// If index exceeds size of the vector, return last element
		else 
			return *(dynamic_buffer+(size-ST_SIZE-1));	
	}
	// If index is still a negative, then return first element
	else
		return static_buffer[0];
}

const int& SmallVector::operator[](int i) const {
	// If index is a negative number, then increase by |size| to 
	// begin from the first element of the SmallVector
	if (i < 0)
		i += size;
	
	if (i >= 0 && i < ST_SIZE) {
		if (i < size)
			return static_buffer[i];
		// If index exceeds size of the vector, return last element
		else 
			return static_buffer[size-1];
	}
	// If index exceeds static buffer
	else if (i >= 0 && i >= ST_SIZE) {
		if (i < size)
			return *(dynamic_buffer+(i-ST_SIZE));
		// If index exceeds size of the vector, return last element
		else 
			return *(dynamic_buffer+(size-ST_SIZE-1));	
	}
	// If index is still a negative, then return first element
	else
		return static_buffer[0];
}

const SmallVector& SmallVector::operator=(const SmallVector &assignment) {
	if (capacity > ST_SIZE) // Destroy the dynamic buffer if allocated
		delete [] dynamic_buffer;
	
	// Allocate dynamic buffer with the new size	
	dynamic_buffer = new int [assignment.getCapacity()-ST_SIZE];
	
	// Copy all the elements from assignment to |this|
	for(int i = 0; i < assignment.getSize(); i++) {
		if (i >= ST_SIZE) {
			*(dynamic_buffer+(i-ST_SIZE)) = *((assignment.dynamic_buffer)+(i-ST_SIZE));
		}
		else {
			*(static_buffer+i) =  *(assignment.static_buffer+i);
		}
	}
	// Assign new size and capacity.
	size = assignment.getSize();
	capacity = assignment.getCapacity();
	return *this;
}

const int SmallVector::getSize() const {
	return size; // Return size
}

const int SmallVector::getCapacity() const {
	return capacity; // Return capacity
}
