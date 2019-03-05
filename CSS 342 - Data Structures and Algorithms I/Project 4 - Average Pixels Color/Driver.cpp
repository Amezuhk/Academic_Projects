// Driver.cpp
// Author:  Khuzaima Mushtaq
// Purpose: This is the driver for the project 4 that executes the project and
//creates the output

#include < iostream >
#include <math.h>
#include "ImageLib.h"
#include "LinkedPixel.h"
#include "newImage.h"
using namespace std;
#pragma once


/*preconditions: all parameters are valid
*postconditions: verifies that the pixel at r, c is not already in a blob, not out of bounds, 
*and is in range to be considered part of a segment
*/
bool isValid(newImage &input, int r, int c,const pixel &seed) {
	int ir = input.getRows(); //input row/col
	int ic = input.getCols();
	if (r < 0 || c < 0 || r > ir || c > ic) {
		return false;
	}
	else {
		pixel thisPixel = input.getPixel(r, c);
		if (thisPixel.blue == 0 && thisPixel.green == 0 && thisPixel.red == 0) { // is in a group already
			return false;
		}
		else {
			if ((abs(seed.red - thisPixel.red) + abs(seed.green - thisPixel.green) + abs(seed.blue - thisPixel.blue)) < 100) { //can be part of segment
				return true;
			}
			return false;
		}
	}
}

/*pre-conditions: all paramaters are valid
*post-conditions: recursively goes through the image and finds a blob following the guidelines for the project.
*/
void recur(newImage &input, newImage &output, LinkedPixel &blob, int r, int c,const  pixel &seed) {
	//abs(seed.red – p.red) + abs(seed.green – p.green) + abs(seed.blue – p.blue) < 100
	if (!isValid(input, r, c, seed)) {
		return;
	}
	else {
		blob.addPixel(input.getPixel(r,c), r, c);
		input.setPixel(r, c, 0, 0, 0); //has already been added to a blob
		recur(input, output, blob, r - 1, c, seed);
		recur(input, output, blob, r + 1, c, seed);
		recur(input, output, blob, r, c - 1, seed);
		recur(input, output, blob, r, c + 1, seed);

	}

}

/*pre-conditions: input is valid
*post-conditions: uses the recur method to find and fill out segments in the output, then writes the output
* and prints total number of segments, the number of pixels in merged, and the average color value for merged
*/
void recursionContainer(newImage input) {
	newImage output = newImage(input.getRows(), input.getCols());
	LinkedPixel merged = LinkedPixel();
	LinkedPixel blob = LinkedPixel();
	int count = 0; //count for how many segments

	//loops through the image and finds the segments
	for (int r = 0; r < input.getRows(); r++) {
		for (int c = 0; c < input.getCols(); c++) {
			pixel thisPixel = input.getPixel(r, c);
			if (thisPixel.blue == 0 && thisPixel.green == 0 && thisPixel.red == 0) {
				// already taken
			}
			else {

				count++;
				pixel seed = input.getPixel(r, c);
				recur(input, output, blob, r, c, seed);
				int or = 0; //output row / col
				int oc = 0;
				merged.merge(blob);
				pixel average = blob.averagePixels();

				//populates the output
				while (blob.getTop(or , oc) == 0) {
					output.setPixel(or , oc, average.red, average.green, average.blue);
				}

			}

		}
	}


	output.WriteImage("output.gif");
	pixel ma = merged.averagePixels(); //merged average
	int mr = ma.red; //merged red
	int mg = ma.green;
	int mb = ma.blue;
	cout << "number of segments: " << count << "number of pixels in merged: " << merged.size() << "average color r, g, b: " << mr << ", " << mg << ", " << mb << endl;
	system("PAUSE");
}



void main() {
	newImage input("fox.gif");
	recursionContainer(input);
}