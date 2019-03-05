#pragma once
#include "bintree.h"
#include "Factory.h"
#include "Book.h"
class BookCollection {
	friend ostream & operator<<(ostream &, const BookCollection&);
public:
	BookCollection();
	~BookCollection();
	void insertAll(istream&);
private:
	BinTree hashArray[26];
	int Hash(char toHash) const;
	Book* toInsert;
	Factory bookFactory;
};