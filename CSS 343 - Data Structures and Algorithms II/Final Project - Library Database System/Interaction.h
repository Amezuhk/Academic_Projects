//--------------------------------------------------------------------
// Interact.h
// Represents an interaction (C, R, D, H) with the library system
// Authors:  Aaron, Sean, Khuzema, Trystan
//--------------------------------------------------------------------
// Interact class: For creating and managing an interaction instance,
//   -- Allows for storing the patron associated with the interaction
//   -- Allows for storing the resource associated with the 
//   interaction
//   -- Allows for storing the library where the interaction is done, //   and time
//
// Implementation and assumptions:
//   -- The libraryID is a constant, representing only one library in 
//	    the system.
//--------------------------------------------------------------------

#pragma once
#include "BookCollection.h"
#include "PatronCollection.h"

class Interact {
public:
	Interact();
	~Interact();
	virtual void create() const = 0;
	virtual Book* getBook() const = 0;
	virtual Patron* getPatron() const = 0;
protected:
	Book* book;// points to item being interacted with
	Patron* patron;
	char iType;
};
