// Rectangle.cpp
// Author:  Khuzaima Mushtaq
// Purpose: Implementation of Rectangle.h

#include < iostream >
#include "Rectangle.h"
using namespace std;
#pragma once

/*Constructor Method
* pre-conditions: N/A
* post-conditions: A new rectangle is initialed with dimentions as provided
* or as 0 if dimentions are not provided
*/
Rectangle::Rectangle(int bR, int bC, int eR, int eC) {
	bRow = bR;
	bCol = bC;
	eRow = eR;
	eCol = eC;
}

/*pre - conditions: bRow is a valid int
* post - conditions : return bRow
*/
int Rectangle::getBR() {
	return bRow;

}

/*pre - conditions: bCol is a valid int
* post - conditions : return bCol
*/
int Rectangle::getBC() {
	return bCol;

}

/*pre - conditions: eRow is a valid int
* post - conditions : return eRow
*/
int Rectangle::getER() {
	return eRow;
}

/*pre - conditions: eCol is a valid int
* post - conditions : return eCol
*/
int Rectangle::getEC() {
	return eCol;

}

/*pre - conditions: bR is a valid int
* post - conditions : set bRow = bR
*/
void Rectangle::setBR(int bR) {
	bRow = bR;

}

/*pre - conditions: bC is a valid int
* post - conditions : set bCol = bC
*/
void Rectangle::setBC(int bC) {
	bCol = bC;
}

/*pre - conditions: eR is a valid int
* post - conditions : set eRow = eR
*/
void Rectangle::setER(int eR) {
	eRow = eR;
}

/*pre - conditions: eC is a valid int
* post - conditions : set eCol = eC
*/
void Rectangle::setEC(int eC) {
	eCol = eC;
}

/*pre - conditions: N/A
* post - conditions : returns true if all rectangle data members
* are equal false if not.
*/

bool Rectangle::operator==(const Rectangle &input) const {
	return ( (bRow == input.bRow) & (bCol == input.bCol) & (eRow == input.eRow) & (eCol == input.eCol) );
}

/*pre - conditions: N/A
* post - conditions : returns false if all rectangle data members
* are equal true if not.
*/
bool Rectangle::operator!=(const Rectangle &input) const {
	return !(*this == input);

}

/* overloaded <<:
* pre-conditions: input is a valid rectangle
* post-conditions: rectangle is output in the form (bRow, bCol) (eRow, eCol)
*/
ostream& operator<<(ostream& output, const Rectangle& input) {
	output << "The Coordinates for this rectangle are: (" << input.bRow << ", " << input.bCol << ") and (" << input.eRow << ", " << input.eCol << ").";
	return output;

}