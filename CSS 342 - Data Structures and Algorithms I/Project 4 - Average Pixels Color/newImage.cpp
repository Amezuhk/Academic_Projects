// newImage.h
// Author:  Khuzaima Mushtaq
// Purpose: Implementation of newImage.h

#include < iostream >
#include "ImageLib.h"
#include "newImage.h"
using namespace std;
#pragma once

/* Constructor Method:
* pre-conditions: fileName is a valid file name
* post-conditions: a newImage is made based on the file being read
*/
newImage::newImage(string fileName) {
	myImage = ReadGIF(fileName);
}

/* Constructor Method:
* pre-conditions: row and col are valid ints ie.  > -1
* post-conditions: a newImage is made of size row x col
* all pixels are black.
*/
newImage::newImage(int row, int col) {
	myImage = CreateImage(row, col);
}

/* Copy Constructor Method:
* pre-conditions: image is a valid image
* post-conditions: a newImage is made which is a copy of image
*/
newImage::newImage(const newImage& image) {
	myImage = CopyImage(image.myImage);
}

/* Destructor Method:
* pre-conditions: N/A
* post-conditions: Deallocates the object
*/
newImage::~newImage() {
	DeallocateImage(myImage);
}

/* pre-conditions: input is valid
* post - conditions : sets this object equal to input
* does not change input
*/
const newImage & newImage::operator=(const newImage &input) {
	if (this != &input) {
		DeallocateImage(myImage);
		myImage = CopyImage(input.myImage);
	}
	return *this;
}

/*pre - conditions: input is valid
* post - conditions : returns true if images are the same in size and all pixels
* are the same false if not.
*/
bool newImage::operator==(const newImage &input) const {
	int cols = input.myImage.cols;
	int rows = input.myImage.rows;
	if (myImage.cols != cols || myImage.rows != rows)
		return false;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			if (myImage.pixels[r][c].red != input.myImage.pixels[r][c].red || (myImage.pixels[r][c].blue != input.myImage.pixels[r][c].blue)
				|| (myImage.pixels[r][c].green != input.myImage.pixels[r][c].green)) { // checks if there are diferences between pixels
				return false;
			}
		}
	}
	return true;
}

/*pre - conditions: input is valid
* post - conditions : returns false if images are the same in size and all pixels
* are the same true if not.
*/
bool newImage::operator!=(const newImage &input) const {
	return !(*this == input);
}

/* overloaded <<:
* pre-conditions: input is a valid image
* post-conditions: rows and cols of image are output
*/
ostream& operator<<(ostream & output, const newImage &r) {
	output << "Number of rows: " << r.myImage.rows << " number of cols: " << r.myImage.cols;
	return output;
}

/*pre - conditions: myImage has valid rows
* post - conditions : returns myImage's rows
*/
int newImage::getRows() const {
	return myImage.rows;
}

/*pre - conditions: myImage has valid cols
* post - conditions : returns myImage's cols
*/
int newImage::getCols() const {
	return myImage.cols;
}

/*pre - conditions: row and col are not out of bounds of myImage
* post - conditions : returns the pixel in myImage at row and col
* if row and col are out of bound returns a black pixel
*/
pixel newImage::getPixel(int row, int col) const {
	if ( (row >= myImage.rows ) || (col >= myImage.cols ) ) {
		newImage e = newImage(1, 1);
		e.setPixel(0, 0, 0, 0, 0);
		return e.getPixel(0,0);
	}
	else {
		return myImage.pixels[row][col];
	}
	
}

/*pre - conditions: row and col are not out of bounds of myImage
* r, g, b are valid rgb values
* post - conditions : sets the pixel in myImage at row col to rgb
* if row and col are out of bound does nothing
*/
void newImage::setPixel(int row, int col, int r, int g, int b) {
	if (row >= myImage.rows || col >= myImage.cols) {
	}
	else {
		myImage.pixels[row][col].red = r;
		myImage.pixels[row][col].green = g;
		myImage.pixels[row][col].blue = b;
	}
}

/*pre - conditions: name is valid and file type extention is valid
* post - conditions : writes image to file as name
*/
void newImage::WriteImage(string name) const {
	WriteGIF(name, myImage);
}


/*pre - conditions: N/A
* post - conditions : returns a newImage that is a flipped version of this object
*/
newImage newImage::flipImage() const {
	newImage output = *this;
	pixel holder; //holds the pixel to be swapped.
	for (int i = 0; i < output.myImage.rows; i++) {
		for (int j = 0; j < output.myImage.cols / 2; j++) {
			int c = (output.myImage.cols - j) - 1; // the column value with which to swap
			holder = output.myImage.pixels[i][j];
			output.myImage.pixels[i][j] = output.myImage.pixels[i][c];
			output.myImage.pixels[i][c] = holder;
		}
	}
	return output;
}

/*pre - conditions: N/A
* post - conditions : returns a newImage that is a photo negatice version of this object
*/
newImage newImage::photoNegative() const {
	newImage output = *this;
	for (int i = 0; i < output.myImage.rows; i++) {
		for (int j = 0; j < output.myImage.cols ; j++) {

			output.myImage.pixels[i][j].blue = 255 - output.myImage.pixels[i][j].blue;
			output.myImage.pixels[i][j].red = 255 - output.myImage.pixels[i][j].red;
			output.myImage.pixels[i][j].green = 255 - output.myImage.pixels[i][j].green;
		}
	}


	return output;

}

/* just some stuff i was messing around with
*/
newImage newImage::changeImage() const {
	newImage output = *this;
	for (int i = 0; i < output.myImage.rows; i++) {
		for (int j = 0; j < output.myImage.cols; j++) {
			if (output.myImage.pixels[i][j].blue >= 128) {
				output.myImage.pixels[i][j].blue = 255;
			}
			else {
				output.myImage.pixels[i][j].blue = 0;
			}


			if (output.myImage.pixels[i][j].green >= 128) {
				output.myImage.pixels[i][j].green = 255;
			}
			else {
				output.myImage.pixels[i][j].green = 0;
			}


			if (output.myImage.pixels[i][j].red >= 128) {
				output.myImage.pixels[i][j].red = 255;
			}
			else {
				output.myImage.pixels[i][j].red = 0;
			}
		}
	}


	return output;

}


