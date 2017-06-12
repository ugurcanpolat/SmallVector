/* @Author
 * Student Name: Ugurcan Polat
 * Student ID : 150140117
 * Date: 30.03.2017
 */

#include <iostream> // std, cout

#include "SmallVector.h"

#define TEST_SIZE 35

using namespace std;

void printSmallVector(const char* const message, const SmallVector& in_vector) { 
	cout << message << ": ";
	for (int i = 0; i < in_vector.getSize(); i++) {
		cout << in_vector[i] << " "; 
	}
	cout << endl;
}

int main() {
	int temp[TEST_SIZE];
	for (int i = 0; i < TEST_SIZE; i++) {
		temp[i] = i;
	}
	SmallVector test(temp, 10);  // Creating SmallVector with 10 elements
	SmallVector test2(temp, 35); // Creating SmallVector with 35 elements
	printSmallVector("Printing test in reverse", test.reverse());
	SmallVector test3; // Empty SmallVector
	test3 = test2 + test; // Concatenate two SmallVectors
	printSmallVector("Printing test3", test3);
	SmallVector test4(test); // Copy SmallVector
	SmallVector test5(temp, 2); // Creating SmallVector with 2 elements
	test5 = test5 * 5; // Replicate elements
	test5.push_back(12); // Add 12 at the end
	test5[0] = 4; // Modify the first element of test5
	cout << "Printing test5 in reverse: ";
	for (int i = 1; i < test5.getSize() + 1; i++) {
		// Testing negative numbers as indices
		cout << test5[-i] << " ";
	}
	cout << endl;
	
	SmallVector a(temp, TEST_SIZE);
	SmallVector b, c;
	b = c = a; // Test assignment operator
	
	printSmallVector("Printing a", a);
	printSmallVector("Printing b", b);
	printSmallVector("Printing c", c);
	
	int pop = a.pop_back(); // Test pop_back
	cout << "Popped element: " << pop << endl;
	a.push_back(temp, 10); // Push first 10 elements of arrary 
	printSmallVector("Printing a", a);
	return 0;
}
