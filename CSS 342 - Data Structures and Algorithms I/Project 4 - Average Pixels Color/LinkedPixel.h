// LinkedPixel.h
// Author:  Khuzaima Mushtaq
// Purpose: This is the header file for the container pixel class for project 4

#include < iostream >
#include "ImageLib.h"
using namespace std;
#pragma once

class LinkedPixel {
	// constructor, copy constructor, operator=, destructor, addPixel, and merge (see below.) You can implement other member functions (including size and averageColor), if desired.
private:

	struct Node { //my linked list struct
		pixel data;
		Node *next;
		int row;
		int col;
	};
	Node *head;

public:
	/*pre-conditions: none
	*post-conditions: a LinkedPixel object is initialied as nullptr
	*/
	LinkedPixel();

	/*pre-conditions: input is a valid object
	*post-conditions: this has all of inputs content and input stays the same
	*/
	LinkedPixel(const LinkedPixel &input);

	/*pre-conditions: input is a valid object
	*post-conditions: set this object = to input all values are same but different objects.
	*/
	const LinkedPixel & operator=(const LinkedPixel &input);

	/*pre-conditions: none
	*post-conditions: all pointers in this list are deleted 
	*/
	~LinkedPixel();

	/*pre-conditions: input is valid
	*post-conditions: adds pixels at the top of the linked list and stores a row and col for them
	*/
	void addPixel(pixel input,int row, int col);

	/*pre-conditions: input is a valid 
	*post-conditions: adds all the items in the input to merge
	*/
	void merge(const LinkedPixel &input);

	/*pre-conditions: none
	*post-conditions: averages the r g b values for all the pixels in the list
	*/
	pixel averagePixels();

	/*pre-conditions: r and c are valid
	*post-conditions: removes top and returns the row and col values for the removed pixel 
	*/
	int getTop(int &r, int &c);

	/*pre-conditions: none
	*post-conditions: returns the size of the list measured by elements
	*/
	int size() const;
};