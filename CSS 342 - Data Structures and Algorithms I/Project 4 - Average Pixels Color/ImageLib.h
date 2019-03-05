/*****************************************************************/
/* ImageLib.h
/*
/* Author: Clark Olson
/*
/* This file describes the interface to the ImageLib library
/* for use by students in CSS 342.  This library provides
/* functionality to read/write GIF images and process them in
/* memory using a procedural style.
/*
/*****************************************************************/

#pragma once

#include <string>
using namespace std;


/* 
 * Type definitions
 */

typedef unsigned char byte;	// A single byte of data

typedef struct {		// A pixel stores 3 bytes of data:
	byte red;		//  intensity of the red component
	byte green;		//  intensity of the green component
	byte blue;		//  intensity of the blue component
	} pixel;


// A simple image data structure:
//   rows is the height of the image (the number of rows of pixels)
//   cols is the width of the image (the number of columns of pixels)
//   pixels is a 2D array of the image pixels
//     The first dimension of pixels varies from 0 to rows-1
//     The second dimension of pixels varies from 0 to cols-1
//   The pixel at row i and column j is accessed by pixels[i][j].
//   With the following definition:
//	image myimage;
//   We could access the red component of the pixel at row 10, column 20 by:
//	myimage.pixels[10][20].red
typedef struct { 
			int   rows, cols;	/* pic size */
			pixel **pixels;		/* image data */
} image;


/*
 * Function prototypes
 */



/*
 * ReadGIF:
 * Preconditions:  filename refers to a file that stores a GIF image.
 * Postconditions: returns the image contained in "filename" using the
 *			conventions described for the image type above.
 *		   If the load is unsuccessful, returns an image with
 *		   rows = 0, cols = 0, pixels = nullptr.
 */

image ReadGIF(string filename);



/*
 * WriteGIF:
 * Preconditions:  filename is valid filename to store a GIF image.
 *		   inputImage holds an image using the conventions described
 *			for the image type above.
 * Postconditions: inputImage is saved as a GIF image at the location
 *			specified by filename.
 */

void WriteGIF(string filename, image inputImage);



/*
 * DeallocateImage:
 * Preconditions:  inputImage contains an image using the conventions
 *		 	for the image type described above.
 * Postconditions: the memory allocated to the pixels of inputImage has
 *			been deallocated.  Also, the image values are set to:
 *			rows = 0, cols = 0, pixels = nullptr.
 */

void DeallocateImage(image &inputImage);



/*
 * CopyImage:
 * Preconditions:  inputImage contains an image using the conventions
 *		 	for the image type described above.
 * Postconditions: if sufficient memory is available, a copy of inputImage
 *			is returned using newly allocated memory.
 *			Otherwise, the returned image has:
 *			rows = 0, cols =0 , pixels = nullptr.
 */

image CopyImage(image inputImage);



/*
 * CreateImage:
 * Preconditions:  rows and cols describe the desired size of the new image.
 * Postconditions: if sufficient memory is available, a new image
 *			is returned using newly allocated memory.
 *			Each pixel has red = 0, green =0, blue = 0.
 *			Otherwise, the returned image has:
 *			rows = 0, cols =0, pixels = nullptr.
 */

image CreateImage(int rows, int cols);


