#pragma once
#include "Book.h"

class Fiction : public Book {

public:
	Fiction();
	~Fiction();
	virtual void create(istream &);
	virtual bool operator<(const Book&) const;
	virtual bool operator>(const Book&) const;
	virtual bool operator==(const Book&) const;
	virtual ostream& print(ostream&) const;
	string author;
};