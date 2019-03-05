// poly.cpp
// Author:  Khuzaima Mushtaq
// Purpose: This is the cpp file for the poly class
#include <iostream>
using namespace std;
#include "poly.h"

// ---------------------------------------------------------------------------
// Default constructor for class Poly
// Preconditions:  None
// Postconditions: arrayPtr is set to nullptr until use
// the size of the polinomial is 0
Poly::Poly() {
	arrayPtr = nullptr;
	size = 0;
}

// Overloaded constructor for class Poly
// Preconditions:  coeff is a real number, pwr is assumed to be zero
// Postconditions: arrayPtr is intialized to 1, and the coeff of pwr
// zero is stored.
Poly::Poly(int coeff) {
	size = 1;
	arrayPtr = new int[size];
	arrayPtr[size - 1] = coeff;
}

// Overloaded constructor for class Poly
// Preconditions:  pwr is non negative the coeff is a real number
// Postconditions: arrayPtr is initialized to the max size needed to 
// represent polinomial of power pwr. all other coeffs are set to zero.
Poly::Poly(int coeff, int pwr) {
	size = pwr + 1;  //size is pwr + 1 because an array of size pwr will
	arrayPtr = new int[size]; // hold pwr - 1 exponents
	arrayPtr[pwr] = coeff;
	for (int i = 0; i < pwr; i++) {
		arrayPtr[i] = 0;
	}
}

// Destructor for class Poly
// Preconditions:  none
// Postconditions: the arrayPtr is deleted and set to nullptr
// to stop memory leaks or hanging pointers
Poly::~Poly() {
	delete[] arrayPtr;
	arrayPtr = nullptr;
}

// Copy constructor for class Poly
// Preconditions: input is valid
// Postconditions: uses the copy method to copy input
Poly::Poly(const Poly &input) {
	copy(input);
}

// private copy method for class Poly
// Preconditions:  toCopy is valid
// Postconditions: make a copy of toCopy without pointing to it
void Poly::copy(const Poly &toCopy) {
	size = toCopy.size;
	arrayPtr = new int[size];
	for (int i = 0; i < size; i++) {
		arrayPtr[i] = toCopy.arrayPtr[i];
	}
}

// set euqal to operator for class Poly
// Preconditions:  input is valid
// Postconditions: savely deletes all currently allocated memory for
// arrayPtr, then uses the copy method to copy input
const Poly & Poly::operator=(const Poly &input) {
	if (&input != this) {
		delete[] arrayPtr;
		copy(input);
	}
	return *this;
}

// coeffcient getting for class Poly
// Preconditions:  pwr is valid, non negative, not out of bounds
// Postconditions: returns the coeffcient of the desied power 
// if it is valid
int Poly::getCoeff(int pwr) const {
	if (pwr >= size || pwr < 0) {
		return 0;
	}
	else {
		return arrayPtr[pwr];
	}
}

// coefficient setter for class Poly
// Preconditions:  pwr is non negative
// Postconditions: sets the coefficient to the correct power
// if the power is greater than the current greatest power
// increase the size of the arrayPtr to be able to store pwr and coeff
// deletes temp and safely erases it from memory
void Poly::setCoeff(int coeff, int pwr) {
	if (pwr < 0) {
		return;
	}
	else if (size < (pwr + 1)) { // extend array
		Poly temp(*this);
		delete[] arrayPtr;
		size = pwr + 1;
		arrayPtr = new int[size];
		arrayPtr[pwr] = coeff;
		for (int i = 0; i < temp.size; i++) {
			arrayPtr[i] = temp.arrayPtr[i];
		}
		for (int i = temp.size; i < pwr; i++) {
			arrayPtr[i] = 0;
		}
		
	}
	else {
		arrayPtr[pwr] = coeff;
	}
}

// private helper method for class Poly
// Preconditions:  can not be used publicly
// Postconditions: creates an array of the desired size with all coeff
// set to 0. used in + and - operations to create the larger of 2 arrays
// to store the sum or the subtration in.
void Poly::setSize(int s) {
	size = s;
	arrayPtr = new int[size];
	for (int i = 0; i < size; i++) {
		arrayPtr[i] = 0;
	}
}


// operator + for class Poly
// Preconditions:  input is valid
// Postconditions: uses polinomial addtion to add input to current
Poly Poly::operator+(const Poly &input) const {
	Poly sum;
	if (input.size == 0) { //input is invalid
		sum = *this;
	}
	//same size array's mean that we can just add them together
	else if (size == input.size) {
		sum.setSize(size);
		for (int i = 0; i < size; i++) {
			sum.arrayPtr[i] = (arrayPtr[i] + input.arrayPtr[i]);
		}


	}
	//size difference means that we have to add some bits and copy other bits
	else if (size > input.size) { 
		sum.setSize(size);
		for (int i = 0; i < input.size; i++) {//add coeffs that can be added
			sum.arrayPtr[i] = (arrayPtr[i] + input.arrayPtr[i]);
		}
		for (int i = input.size; i < size; i++) {//copy coeffs
			sum.arrayPtr[i] = arrayPtr[i];
		}
	}
	//size difference means that we have to add some bits and copy other bits
	else if (size < input.size) {
		sum.setSize(input.size);
		for (int i = 0; i < size; i++) { //add coeffs that can be added
			sum.arrayPtr[i] = (arrayPtr[i] + input.arrayPtr[i]);
		}
		for (int i = size; i < input.size; i++) { //copy coeffs
			sum.arrayPtr[i] = input.arrayPtr[i];
		}
	}
	return sum;

}

// operator - for class Poly
// Preconditions:  input is valid
// Postconditions: uses polinomial subtration to subtract input 
// from current
Poly Poly::operator-(const Poly &input) const {
	Poly output;
	if (input.size == 0) { //input is invalid
		output = *this;
	}
	//same size array's mean that we can just subtract them
	else if (size == input.size) {
		output.setSize(size);
		for (int i = 0; i < size; i++) {
			output.arrayPtr[i] = (arrayPtr[i] - input.arrayPtr[i]);
		}


	}
	//size difference means that we have to subtract some bits and 
	//copy other bits
	else if (size > input.size) {
		output.setSize(size);
		for (int i = 0; i < input.size; i++) {
			output.arrayPtr[i] = (arrayPtr[i] - input.arrayPtr[i]);
		}
		for (int i = input.size; i < size; i++) {
			output.arrayPtr[i] = arrayPtr[i];
		}
	}
	else if (size < input.size) {
		output.setSize(input.size);
		for (int i = 0; i < size; i++) {
			output.arrayPtr[i] = (arrayPtr[i] - input.arrayPtr[i]);
		}
		for (int i = size; i < input.size; i++) {
			output.arrayPtr[i] = (input.arrayPtr[i] * -1);
		}
	}
	return output;
}

// operator * for class Poly
// Preconditions:  input is valid
// Postconditions: uses polinomial multiplication (multiply all the terms
// from one side with all the terms of the other size.)
Poly Poly::operator*(const Poly &input) const {
	Poly product;
	product.setSize((size + input.size) - 1); //max pwr possible

	for (int i = 0; i < size; i++) { //all the first terms
		for (int j = 0; j < input.size; j++) { //all the second terms
			product.arrayPtr[i + j] += arrayPtr[i] * input.arrayPtr[j];
		}
	}

	return product;
}

// operator *= for class Poly
// Preconditions:  operator * works as intended
// Postconditions: uses * operator to multiply self with input to provide
// result
Poly& Poly::operator*=(const Poly &input) {
	*this = *this * input;
	return *this;
}

// operator += for class Poly
// Preconditions:  operator + works as intended
// Postconditions: uses + operator to add self to input to provide
// result
Poly& Poly::operator+=(const Poly &input) {
	*this = *this + input;
	return *this;

}

// operator -= for class Poly
// Preconditions:  operator - works as intended
// Postconditions: uses - operator to subtract self from input to provide
// result
Poly& Poly::operator-=(const Poly &input) {
	*this = *this - input;
	return *this;
}

// operator == for class Poly
// Preconditions:  none
// Postconditions: compares highest power and all power values
// to determin if both polinomials are equal
bool Poly::operator==(const Poly &input) const {
	if (size != input.size) {
		return false;
	}
	else {
		for (int i = 0; i < size; i++) {
			if (arrayPtr[i] != input.arrayPtr[i]) {
				return false;
			}
		}
		return true;
	}
}

// operator != for class Poly
// Preconditions:  operator == works as intended
// Postconditions: uses == operator to determin if !=
bool Poly::operator!=(const Poly &input) const {
	return !(*this == input);
}

//Overloaded output operator for class poly;
// Preconditions:  poly exists
// Postconditions: outputs the polynomial as described in the assignment lab1
ostream& operator<<(ostream &output, const Poly &input) {
	if (input.size == 0) { //poly doesnt exist
		output << "0";
	}
	else if (input.size == 1) { //poly has one term
		output << input.arrayPtr[0];
	}
	else { //poly has multiple terms
		for (int i = input.size - 1; i >= 0; i--) {
			if (input.arrayPtr[i] == 0) { //this term is zero
				//Do Nothing
			}
			else {
				if (i == 0) {// doesnt show x for terms x^0
					if(input.arrayPtr[i] > 0) // checks is coeff is + or -
						output << " +" << input.arrayPtr[i]; 
					else
						output << " " << input.arrayPtr[i]; 
				}
				else if (i == 1) {// doesnt show exponent for terms x^1
					if (input.arrayPtr[i] > 0)// checks is coeff is + or -
						output << " +" << input.arrayPtr[i] << "x" ;
					else
						output << " " << input.arrayPtr[i] << "x";
				}
				else {
					if (input.arrayPtr[i] > 0)// checks is coeff is + or -
						output << " +" << input.arrayPtr[i] << "x^" << i ;
					else
						output << " " << input.arrayPtr[i] << "x^" << i ;
				}	
			}
		}
	}
	return output;
}

//Overloaded output operator for class poly;
// Preconditions:  there is a user
// Postconditions: asks for valid inputs from use to set valid values for
// the polinomial
istream& operator>>(istream &input, Poly &P) {
	int pwr = 0;
	int coeff = 0;
	bool exit = false;

	while (!exit) {
		input >> coeff >> pwr; 
		if (coeff == -1 && pwr == -1) { //end condition
			exit = true;
		}
		else {
			P.setCoeff(coeff, pwr);
		}
	}
	return input;

}
