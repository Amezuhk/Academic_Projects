/*****************************************************************/
/* main.cpp
/*
/* Author: Khuzaima Mushtaq
/*
/* This file contains the code for project 1. It reads in an image file "test.gif" and
/* modifies it according to the Project 1 instructions and outputs an 
/* image file called "output.gif". It also compares the output.gif to the modified file
/* and outputs the differences to console
/* 
/*****************************************************************/

#pragma once

#include "ImageLib.h"
#include <iostream>
using namespace std;

//Forward Declarations
void flipImage(image input);
void changeImageRed(pixel &p, int col);
void changeImagePixels(image input);
void changeImageBlue(pixel &p, int row);
int compareImagePixels(pixel **i, pixel **o, int rows, int cols);

/*
Preconditions: test.gif exists and is a valid image file.
postconditions: a modified version of test.gif is written to disk as 
output.gif and the differences between output.gif and the modified test.gif 
are output to console.
*/
int main() {	
	image input = ReadGIF("test.gif");
	if (input.rows == 0) return -1;

	changeImagePixels(input); //changes test.gif as required.
	flipImage(input);        // flips test.gif as required.

	WriteGIF("output.gif", input); //outputs the changed image.

	image output = ReadGIF("output.gif"); //reads the changed image back in.

	int differences = compareImagePixels(input.pixels, //counts the differences between output.
		output.pixels, input.rows, input.cols); // and the modified test.gif, and stores them.
	                                            
	cout << "Total differences: " << differences << endl;
	system("PAUSE");

	DeallocateImage(input); 
	DeallocateImage(output);
	return 0;

}

/*parameters: i, the first image's pixel array. (input)
          o, the second image's pixel array. (output)
		  rows, the length of the arrays.
		  cols, the width of the arrays.
Preconditions: The arrays passed in are valid and no shorter than row and cols.
Postconditions: returns the number of differences between the two images.
*/
int compareImagePixels(pixel **i, pixel **o, int rows, int cols) {
	int differences = 0;

	return differences;
}
/*parameters: input, the image to be modified.
Preconditions: the image is a valid image.
Postconditions: input is modified as directed.
*/
void changeImagePixels(image input) {
	for (int r = 0; r < input.rows; r++) {
		for (int c = 0; c < input.cols; c++) {
			changeImageBlue(input.pixels[r][c], r); //changes pixel's blue
			changeImageRed(input.pixels[r][c], c); //changes pixel's red
		}
	}
}
/*parameters: p, the pixel to be changed, passed by reference.
              col, the colum position of the pixel in the image
			       which is used to modify the image properly.
Preconditions: the pixel and the col passed in are valid.
Postconditions: The red element of the pixel is changed as required.
*/
void changeImageRed(pixel &p, int col) {
	if (p.red + (col % 9) > 255) {
		p.red = 255;
	}else {
		p.red = p.red + (col % 9);
	}
}

/*parameters: p, the pixel to be changed, passed by reference.
              row, the row position of the pixel in the image
              which is used to modify the image properly.
Preconditions: the pixel and the row values passed in are valid.
Postconditions: The blue element of the pixel is changed as required.
*/
void changeImageBlue(pixel &p, int row) {
	if (p.blue - (row % 7) < 0) {
		p.blue = 0;
	}
	else {
		p.blue = p.blue - (row % 7);
	}
}

/*parameters: input, the image file to be flipped.
Preconditions: input is a valid file.
Postconditions: input is flipped horizontally (mirror image) as required.
*/
void flipImage(image input) {
	pixel holder; //holds the pixel to be swapped.
	for (int i = 0; i < input.rows; i++) {
		for (int j = 0; j < input.cols / 2; j++) {
			int c = (input.cols - j) - 1; // the column value with which to swap
			holder = input.pixels[i][j];
			input.pixels[i][j] = input.pixels[i][c];
			input.pixels[i][c] = holder;
		}
	}
}