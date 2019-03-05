// Rectangle.h
// Author:  Khuzaima Mushtaq
// Purpose: This is the header class for the Rectangle class.
// it stores 4 int's which are coordinated for a rectangle's 
// top left and bottom right cornor

#include < iostream >
using namespace std;
#pragma once

class Rectangle {

	/* overloaded <<: 
	* pre-conditions: input is a valid rectangle
	* post-conditions: rectangle is output in the form (bRow, bCol) (eRow, eCol)
	*/
	friend ostream& operator<<(ostream&, const Rectangle& input);

private:
	int bRow; //top left row coordinate
	int bCol; //top left colum coordinate
	int eRow; //bottom right row coordinate
	int eCol; //bottom right colum coordinate

public:
	/*Constructor Method
	* pre-conditions: N/A
	* post-conditions: A new rectangle is initialed with dimentions as provided
	* or as 0 if dimentions are not provided
	*/
	Rectangle(int bR = 0, int bC = 0, int eR = 0, int eCol = 0);

	/*pre - conditions: bRow is a valid int
	* post - conditions : return bRow
	*/
	int getBR();

	/*pre - conditions: bCol is a valid int
	* post - conditions : return bCol
	*/
	int getBC();

	/*pre - conditions: eRow is a valid int
	* post - conditions : return eRow
	*/
	int getER();

	/*pre - conditions: eCol is a valid int
	* post - conditions : return eCol
	*/
	int getEC();

	/*pre - conditions: bR is a valid int
	* post - conditions : set bRow = bR
	*/
	void setBR(int bR);

	/*pre - conditions: bC is a valid int
	* post - conditions : set bCol = bC
	*/
	void setBC(int bC);

	/*pre - conditions: eR is a valid int
	* post - conditions : set eRow = eR
	*/
	void setER(int eR);

	/*pre - conditions: eC is a valid int
	* post - conditions : set eCol = eC
	*/
	void setEC(int eC);

	/*pre - conditions: N/A
	* post - conditions : returns true if all rectangle data members
	* are equal false if not.
	*/
	bool operator==(const Rectangle &input) const;

	/*pre - conditions: N/A
	* post - conditions : returns false if all rectangle data members
	* are equal true if not.
	*/
	bool operator!=(const Rectangle &input) const;
};