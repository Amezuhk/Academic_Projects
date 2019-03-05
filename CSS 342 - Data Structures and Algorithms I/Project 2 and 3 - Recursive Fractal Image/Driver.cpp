// Driver.cpp
// Author:  Khuzaima Mushtaq
// Purpose: This is the driver class for Assignment 3
// it uses the newImage class and the Rectangle class to 
// make the project 3 image pattern.
#include "newImage.h"
#include "Rectangle.h"
#include <iostream>
using namespace std;
#pragma once

/*pre-conditions: input and output are valid, input is 2x output
* post-conditions: return an output image which is the smaller version of input
* using the algorithm described in hw assignment for getting pixels in output
*/
newImage helpMakeSmaller(newImage input,newImage output) {

	//output(r, c) = (input(2r, 2c) + input(2r+1, 2c) + input(2r, 2c+1) + input(2r+1, 2c+1) ) / 4

	for (int r = 0; r < output.getRows(); r++) {
		for (int c = 0; c < output.getCols(); c++) {

			pixel a = output.getPixel(r, c); //pixel to be changed

			a.red += (input.getPixel(2 * r, 2 * c).red / 4); // averages all the red pixels
			a.red += (input.getPixel(2 * r + 1, 2 * c).red / 4);
			a.red += (input.getPixel(2 * r, 2 * c + 1).red / 4);
			a.red += (input.getPixel(2 * r + 1, 2 * c + 1).red / 4);

			a.blue += (input.getPixel(2 * r, 2 * c).blue / 4); // averages all the blue pixels
			a.blue += (input.getPixel(2 * r + 1, 2 * c).blue / 4);
			a.blue += (input.getPixel(2 * r, 2 * c + 1).blue / 4);
			a.blue += (input.getPixel(2 * r + 1, 2 * c + 1).blue / 4);

			a.green += (input.getPixel(2 * r, 2 * c).green / 4); // averages all the green pixels
			a.green += (input.getPixel(2 * r + 1, 2 * c).green / 4);
			a.green += (input.getPixel(2 * r, 2 * c + 1).green / 4);
			a.green += (input.getPixel(2 * r + 1, 2 * c + 1).green / 4);

			output.setPixel(r, c, a.red, a.green, a.blue);



		}
	}
	return output;
}

/*pre-conditions: input and output are valid, input is 2x output
* post-conditions: return an output image which is the smaller flipped version of input
* using the algorithm described in hw assignment for getting pixels in output
*/
newImage helpMakeSmallerFlipped(newImage input, newImage output) {
	int maxR = input.getRows() - 1;
	int maxC = input.getCols() - 1;

	if (input.getRows() == 1) {
		maxR = 1;  //otherwise it tried to get a pixel at -1
	}
	if (input.getCols() == 1) {

		maxC = 1; //otherwise it tried to get a pixel at -1
	}

	for (int r = 0; r < output.getRows(); r++) {
		for (int c = 0; c < output.getCols(); c++) {

			pixel a = output.getPixel(r, c); // pixel to be changed

			a.red += (input.getPixel(maxR - (2 * r), maxC - (2 * c)).red / 4); // averages all the red pixels
			a.red += (input.getPixel(maxR - (2 * r) - 1, maxC - (2 * c)).red / 4);
			a.red += (input.getPixel(maxR - (2 * r), maxC - (2 * c) - 1).red / 4);
			a.red += (input.getPixel(maxR - (2 * r) - 1, maxC - (2 * c) - 1).red / 4);

			a.blue += (input.getPixel(maxR - (2 * r), maxC - (2 * c)).blue / 4); // averages all the blue pixels
			a.blue += (input.getPixel(maxR - (2 * r) - 1, maxC - (2 * c)).blue / 4);
			a.blue += (input.getPixel(maxR - (2 * r), maxC - (2 * c) - 1).blue / 4);
			a.blue += (input.getPixel(maxR - (2 * r) - 1, maxC - (2 * c) - 1).blue / 4);

			a.green += (input.getPixel(maxR - (2 * r), maxC - (2 * c)).green / 4); // averages all the green pixels
			a.green += (input.getPixel(maxR - (2 * r) - 1, maxC - (2 * c)).green / 4);
			a.green += (input.getPixel(maxR - (2 * r), maxC - (2 * c) - 1).green / 4);
			a.green += (input.getPixel(maxR - (2 * r) - 1, maxC - (2 * c) - 1).green / 4);

			output.setPixel(r, c, a.red, a.green, a.blue);
		}
	}
	return output;
}

/*pre-conditions: input is valid
* post-conditions: return an output image using helpMakeSmaller which is the smaller version of input
* using the algorithm described in hw assignment for getting pixels in output
*/
newImage makeSmaller(newImage input) {

	newImage output;
	if (input.getRows() == 1 && input.getCols() == 1) { // input cant be any smaller without being 0,0
		output = newImage(1, 1);
		return helpMakeSmaller(input, output);
	}
	else if (input.getRows() == 1) { //if rows are 1 then they can't be any smaller but cols can be
		output = newImage(1, input.getCols() / 2);
		return helpMakeSmaller(input, output);
	}
	else if (input.getCols() == 1) { // if cols are 1 then they can't be any smaller but rows can be
		output = newImage((input.getRows() / 2), 1);
		return helpMakeSmaller(input, output);
	}
	else { //neither rows nor col are 1 then they can be smaller
		output = newImage((input.getRows() / 2), input.getCols() / 2);
		return helpMakeSmaller(input, output);
	}
}

/*pre-conditions: input is valid
* post-conditions: return an output image using helpMakeSmallerFlipped which is the smaller flipped version of input
* using the algorithm described in hw assignment for getting pixels in output
*/
newImage makeSmallerFlipped(newImage input) {

	newImage output;

	if (input.getRows() == 1 && input.getCols() == 1) { // input cant be any smaller without being 0,0
		output = newImage(1, 1);
		return helpMakeSmallerFlipped(input, output);
	}
	else if (input.getRows() == 1) {
		output = newImage(1, input.getCols() / 2); //if rows are 1 then they can't be any smaller but cols can be
		return helpMakeSmallerFlipped(input, output);
	}
	else if (input.getCols() == 1) {
		output = newImage(input.getRows() / 2, 1); // if cols are 1 then they can't be any smaller but rows can be
		return helpMakeSmallerFlipped(input, output);
	}
	else { //neither rows nor col are 1 then they can be smaller
		output = newImage(input.getRows() / 2, input.getCols() / 2);
		return helpMakeSmallerFlipped(input, output);
	}
}

/*Pre-conditions: input, R, and output are all valid
* Post-conditions: returns an Image the size of the Input image
* which follows the proper pattern as described by the assgignment 3
*/
void recur(newImage input, Rectangle R, newImage &output) {
	
	// These half way points are used to determine the top left, bottom right,
	// bottom left, and top right, quardrants of R
	// which are used to define where we draw the smaller and flipped images 
	// and the size of rectangle that we pass in the recursive call
	int Rhelp = R.getBR() + ((R.getER() - R.getBR()) / 2); //half way row point of R
	int Chelp = R.getBC() + ((R.getEC() - R.getBC()) / 2); //half way col point of R




	if (input.getRows() == 1 && input.getCols() == 1) { //Base case
		pixel a = input.getPixel(0, 0);

		for (int r = R.getBR(); r <= Rhelp; r++) {  //fills out the R with the one pixel left in input
			for (int c = R.getBC(); c <= Chelp; c++) {
				int b = r - R.getBR();
				int d = c - R.getBC();
				if (b >= input.getRows() && b != 0)
					b = input.getRows() - 1;
				if (d >= input.getCols() && d != 0)
					d = input.getCols() - 1;
				output.setPixel(r, c, a.red, a.green, a.blue);
			}
		}

		for (int r = Rhelp; r < R.getER(); r++) { //fills out the R with the one pixel left in input
			for (int c = Chelp; c < R.getEC(); c++) {
				int b = r - Rhelp;
				int d = c - Chelp;
				if (b >= input.getRows() && b != 0)
					b = input.getRows() - 1;
				if (d >= input.getCols() && d != 0)
					d = input.getCols() - 1;
				output.setPixel(r, c, a.red, a.green, a.blue);
			}
		}
	}
	else { //recursive case

		newImage flipped = makeSmallerFlipped(input); //makes input flipped and smaller
		input = makeSmaller(input); //makes input smaller

			for (int r = R.getBR(); r < Rhelp; r++) { //fills out the top left quadrent with the smaller input image
				for (int c = R.getBC(); c < Chelp; c++) {
					int b = r - R.getBR();
					int d = c - R.getBC();
					if (b >= input.getRows() && b != 0)
						b = input.getRows() - 1;
					if (d >= input.getCols() && d != 0)
						d = input.getCols() - 1;
					pixel a = input.getPixel(b, d);
					output.setPixel(r, c, a.red, a.green, a.blue);
				}
			}

		for (int r = Rhelp; r < R.getER(); r++) { //fills out the bottom right quadrent with the flipped input image
			for (int c = Chelp; c < R.getEC(); c++) {
				int b = r - Rhelp;
				int d = c - Chelp;
				if (b >= input.getRows() && b != 0)
					b = input.getRows() - 1;
				if (d >= input.getCols() && d != 0)
					d = input.getCols() - 1;
				pixel a = flipped.getPixel(b, d);
				output.setPixel(r, c, a.red, a.green, a.blue);
			}
		}

		Rectangle lower = Rectangle(Rhelp, R.getBC(), R.getER(), Chelp); //the bottom left rectangle for the first recursice call
		recur(input, lower, output); //first recursice call

		Rectangle upper = Rectangle(R.getBR(), Chelp, Rhelp, R.getEC()); //top right rectangle for the second recursive call
		recur(input, upper, output); //second recursive call
	}
}

/*Pre-conditions: input is valid
* Post-conditions: returns an Image the size of the Input image
* which follows the proper pattern as described by the assgignment 3
* uses the recur method to accomplish the task
*/
newImage useRecur(newImage input) { 
	Rectangle R = Rectangle(0, 0, input.getRows(), input.getCols()); //defines the initial rectangle size based on input
	newImage output = newImage(input.getRows(), input.getCols()); //defines a newImage output the size of input on which we will output the pattern

	recur(input, R, output); //recrusive method call

	return output; //the output image with the pattern
}

/*pre-conditions: input is taken from a valid file, test.gif is a valid file
* post-conditions: writes an image to disk called "output.gif" which is
* the pattern of input image as described in assignment 3
*/
int main() {
	newImage input = newImage("fox.gif"); //initialization

	input = useRecur(input); // where the recursion happens

	input.WriteImage("output.gif"); //writes output to disk
}
