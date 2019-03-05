#pragma once
#include "Book.h"

class Youth : public Book {

public:
	Youth();
	~Youth();
	virtual void create(istream &);
	virtual bool operator<(const Book&) const;
	virtual bool operator>(const Book&) const;
	virtual bool operator==(const Book&) const;
	virtual ostream& print(ostream&) const;
	string author;

};