#pragma once
#include "Book.h"

class Periodical : public Book {

public:
	Periodical();
	~Periodical();
	virtual void create(istream &);
	virtual bool operator<(const Book&) const;
	virtual bool operator>(const Book&) const;
	virtual bool operator==(const Book&) const;
	virtual ostream& print(ostream&) const;
	int year;
	int month;
};