#pragma once
#include "Factory.h"
#include "Patron.h"

class PatronCollection {
public:
	PatronCollection();
	~PatronCollection();
	void insertAll(istream&);
	void displayP();

private:
	Patron pHashArray[211]; //Patron hash array, 211 prime number
	int Hash(int toHash);   
	int Hash2(int toHash);
};
