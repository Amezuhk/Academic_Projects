// LinkedPixel.cpp
// Author:  Khuzaima Mushtaq
// Purpose: This is the cpp file for the container pixel class for project 4

#include < iostream >
#include "ImageLib.h"
#include "LinkedPixel.h"
using namespace std;
#pragma once

/*pre-conditions: none
*post-conditions: a LinkedPixel object is initialied as nullptr
*/
LinkedPixel::LinkedPixel() {
	head = nullptr;
}

/*pre-conditions: input is a valid object
*post-conditions: this has all of inputs content and input stays the same
*/
LinkedPixel::LinkedPixel(const LinkedPixel &input) {

	if (input.head == nullptr) {
		head = nullptr; // original list is empty
		head->col = 0;
		head->row = 0;

	}else {
		// copy first node
		head = new Node;
		head->data = input.head->data;
		Node *cur = input.head;
		Node *newCur = head;

		// copy rest of List

		while (cur->next != nullptr) {

			cur = cur->next;
			newCur->next = new Node;
			newCur = newCur->next;
			newCur->data = cur->data;
			newCur->col = cur->col;
			newCur->row = cur->row;

		}

		newCur->next = nullptr;
	}
}

/*pre-conditions: none
*post-conditions: all pointers in this list are deleted
*/
LinkedPixel::~LinkedPixel() {
	while (head != nullptr) {
		Node *cur = head;
		head = head->next;
		delete cur;
	}
}


/*pre-conditions: input is a valid object
*post-conditions: set this object = to input all values are same but different objects.
*/
const LinkedPixel & LinkedPixel::operator=(const LinkedPixel &input) {
	//delete current list
	while (head != nullptr) {
		Node *cur = head;
		head = head->next;
		delete cur;
	}

	if (input.head == nullptr) {
		head = nullptr; // input list is empty

	}
	else {
		head = new Node;
		head->data = input.head->data;
		Node *cur = input.head;
		Node *newCur = head;

		// copy rest of List

		while (cur->next != nullptr) {

			cur = cur->next;
			newCur->next = new Node;
			newCur = newCur->next;
			newCur->data = cur->data;
			newCur->col = cur->col;
			newCur->row = cur->row;

		}

		newCur->next = nullptr;
	}
	return *this;
}

/*pre-conditions: input is valid
*post-conditions: adds pixels at the top of the linked list and stores a row and col for them
*/
void LinkedPixel::addPixel(pixel input, int row, int col) {

	if (head == nullptr) {
		head = new Node;
		head->data = input;
		head->col = col;
		head->row = row;
		head->next = nullptr;
	}
	else {
		//make new node
		Node *newNode = new Node;
		newNode->data = input;
		newNode->row = row;
		newNode->col = col;

		//insert new node at head
		newNode->next = head;
		head = newNode;

	}
}

/*pre-conditions: input is a valid
*post-conditions: adds all the items in the input to merge
*/
void LinkedPixel::merge(const LinkedPixel &input) {
	if (input.head == nullptr) {
		// do nothing
	}
	else {
		Node *cur = input.head;
		while (cur != nullptr) {
			addPixel(cur->data, cur->row, cur->col);
			cur = cur->next;
		}
	}
}

/*pre-conditions: none
*post-conditions: averages the r g b values for all the pixels in the list
*/
pixel LinkedPixel::averagePixels() {
	pixel toBeReturned = pixel();
	if (head == nullptr) {
		toBeReturned.red = 0;
		toBeReturned.green = 0;
		toBeReturned.blue = 0;
		return toBeReturned;
	}
	int r = 0;
	int g = 0;
	int b = 0;
	int count = 0;
	Node *cur = head;
	while (cur != nullptr) {
		r += cur->data.red;
		g += cur->data.green;
		b += cur->data.blue;
		count++;
		cur = cur->next;
	}
	r = r / count;
	g = g / count;
	b = b / count;
	toBeReturned = pixel();
	toBeReturned.red = r;
	toBeReturned.green = g;
	toBeReturned.blue = b;
	return toBeReturned;
}

/*pre-conditions: r and c are valid
*post-conditions: removes top and returns the row and col values for the removed pixel
*/
int LinkedPixel::getTop(int &r, int &c) {
	if (head == nullptr) {
		return 1;
	}
	else {
		r = head->row;
		c = head->col;
		Node *cur = head;
		head = head->next;
		delete cur;
		cur = nullptr;
		return 0;
	}

}

/*pre-conditions: none
*post-conditions: returns the size of the list measured by elements
*/
int LinkedPixel::size() const {
	int size = 0;
	Node *cur = head;
	while (cur != nullptr) {
		size++;
		cur = cur->next;
	}
	return size;
}

