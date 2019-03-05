// poly.h
// Author:  Khuzaima Mushtaq
// Purpose: This is the header file for my polinomial

#include <iostream>
using namespace std;
#pragma once

// ---------------------------------------------------------------------------

class Poly {

	//Overloaded output operator for class poly;
	// Preconditions:  poly exists
	// Postconditions: outputs the polynomial as described in the assignment lab1
	friend ostream& operator<<(ostream &, const Poly &);

	//Overloaded output operator for class poly;
	// Preconditions:  there is a user
	// Postconditions: asks for valid inputs from use to set valid values for
	// the polinomial
	friend istream& operator >> (istream &, Poly &);

public:

	// Default constructor for class Poly
	// Preconditions:  None
	// Postconditions: arrayPtr is set to nullptr until use
	// the size of the polinomial is 0
	Poly();

	// Overloaded constructor for class Poly
	// Preconditions:  coeff is a real number, pwr is assumed to be zero
	// Postconditions: arrayPtr is intialized to 1, and the coeff of pwr
	// zero is stored.
	Poly(int);

	// Overloaded constructor for class Poly
	// Preconditions:  pwr is non negative the coeff is a real number
	// Postconditions: arrayPtr is initialized to the max size needed to 
	// represent polinomial of power pwr. all other coeffs are set to zero.
	Poly(int, int);

	// Destructor for class Poly
	// Preconditions:  none
	// Postconditions: the arrayPtr is deleted and set to nullptr
	// to stop memory leaks or hanging pointers
	~Poly();

	// Copy constructor for class Poly
	// Preconditions: input is valid
	// Postconditions: uses the copy method to copy input
	Poly(const Poly &input); //copy constructor

	// set euqal to operator for class Poly
	// Preconditions:  input is valid
	// Postconditions: savely deletes all currently allocated memory for
	// arrayPtr, then uses the copy method to copy input
	const Poly & operator=(const Poly &input);

	// coeffcient getting for class Poly
	// Preconditions:  pwr is valid, non negative, not out of bounds
	// Postconditions: returns the coeffcient of the desied power 
	// if it is valid
	int getCoeff(int) const;
	
	// coefficient setter for class Poly
	// Preconditions:  pwr is non negative
	// Postconditions: sets the coefficient to the correct power
	// if the power is greater than the current greatest power
	// increase the size of the arrayPtr to be able to store pwr and coeff
	// deletes temp and safely erases it from memory
	void setCoeff(int, int);

	// operator + for class Poly
	// Preconditions:  input is valid
	// Postconditions: uses polinomial addtion to add input to current
	Poly operator+(const Poly &) const;

	// operator - for class Poly
	// Preconditions:  input is valid
	// Postconditions: uses polinomial subtration to subtract input 
	// from current
	Poly operator-(const Poly &) const;  

	// operator * for class Poly
	// Preconditions:  input is valid
	// Postconditions: uses polinomial multiplication (multiply all the terms
	// from one side with all the terms of the other size.)
	Poly operator*(const Poly &) const;  

	// operator == for class Poly
	// Preconditions:  none
	// Postconditions: compares highest power and all power values
	// to determin if both polinomials are equal
	bool operator==(const Poly &) const;     

	// operator != for class Poly
	// Preconditions:  operator == works as intended
	// Postconditions: uses == operator to determin if !=
	bool operator!=(const Poly &) const;      
	
	// operator += for class Poly
	// Preconditions:  operator + works as intended
	// Postconditions: uses + operator to add self to input to provide
	// result
	Poly& operator+=(const Poly &); 

	// operator -= for class Poly
	// Preconditions:  operator - works as intended
	// Postconditions: uses - operator to subtract self from input to provide
	// result
	Poly& operator-=(const Poly &); 

	// operator *= for class Poly
	// Preconditions:  operator * works as intended
	// Postconditions: uses * operator to multiply self with input to provide
	// result
	Poly& operator*=(const Poly &);       

private:

	// private helper method for class Poly
	// Preconditions:  can not be used publicly
	// Postconditions: creates an array of the desired size with all coeff
	// set to 0. used in + and - operations to create the larger of 2 arrays
	// to store the sum or the subtration in.
	void setSize(int);

	// private copy method for class Poly
	// Preconditions:  toCopy is valid
	// Postconditions: make a copy of toCopy without pointing to it
	void copy(const Poly &);

	int* arrayPtr; //dynamic array
	int size; //array size
	
};