#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Book {
	friend ostream & operator<<(ostream &, const Book &);
public:

	Book();
	~Book();
	virtual void create(istream &) = 0;
	// comparison operators
	virtual bool operator<(const Book&) const = 0;
	virtual bool operator>(const Book&) const = 0;
	virtual bool operator==(const Book&) const = 0;
	virtual ostream& print(ostream&) const;

	string genre;
	string title;
	string year;
	int totalNumber;
	int nAvail;

};