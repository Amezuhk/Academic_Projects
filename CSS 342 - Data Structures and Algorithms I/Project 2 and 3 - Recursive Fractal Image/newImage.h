// newImage.h
// Author:  Khuzaima Mushtaq
// Purpose: This is the header class for my newImage class from project 2
// defines all the data members/ mehtods for myImage class as described in project 2

#include < iostream >
#include "ImageLib.h"
using namespace std;
#pragma once
class newImage {

/* overloaded <<:
* pre-conditions: input is a valid image
* post-conditions: rows and cols of image are output
*/
friend ostream& operator<<(ostream&, const newImage& input);

private:
	image myImage;


public:
	/* Constructor Method:
	* pre-conditions: fileName is a valid file name
	* post-conditions: a newImage is made based on the file being read
	*/
	newImage(string fileName);

	/* Constructor Method:
	* pre-conditions: row and col are valid ints ie.  > -1
	* post-conditions: a newImage is made of size row x col 
	* all pixels are black.
	*/
	newImage(int row = 0, int Col = 0);

	/* Copy Constructor Method:
	* pre-conditions: image is a valid image
	* post-conditions: a newImage is made which is a copy of image
	*/
	newImage(const newImage& image);

	/* Destructor Method:
	* pre-conditions: N/A
	* post-conditions: Deallocates the object
	*/
	newImage::~newImage();

	/* pre-conditions: input is valid
	* post - conditions : sets this object equal to input
	* does not change input
	*/
	const newImage & operator=(const newImage &input);

	/*pre - conditions: input is valid
	* post - conditions : returns true if images are the same in size and all pixels 
	* are the same false if not.
	*/
	bool operator==(const newImage &input) const;

	/*pre - conditions: input is valid
	* post - conditions : returns false if images are the same in size and all pixels
	* are the same true if not.
	*/
	bool operator!=(const newImage &input) const;

	/*pre - conditions: N/A
	* post - conditions : returns a newImage that is a flipped version of this object
	*/
	newImage flipImage() const;

	/*pre - conditions: N/A
	* post - conditions : returns a newImage that is a photo negatice version of this object
	*/
	newImage photoNegative() const;

	/*pre - conditions: name is valid and file type extention is valid
	* post - conditions : writes image to file as name
	*/
	void WriteImage(string name) const;
	/* just some stuff i was messing around with
	*/
	newImage changeImage() const;

	/*pre - conditions: myImage has valid rows
	* post - conditions : returns myImage's rows
	*/
	int getRows();

	/*pre - conditions: myImage has valid cols
	* post - conditions : returns myImage's cols
	*/
	int getCols();

	/*pre - conditions: row and col are not out of bounds of myImage
	* post - conditions : returns the pixel in myImage at row and col
	* if row and col are out of bound returns a black pixel
	*/
	pixel getPixel(int row, int col);

	/*pre - conditions: row and col are not out of bounds of myImage
	* r, g, b are valid rgb values
	* post - conditions : sets the pixel in myImage at row col to rgb
	* if row and col are out of bound does nothing
	*/
	void setPixel(int row, int col, int r, int g, int b);
};



