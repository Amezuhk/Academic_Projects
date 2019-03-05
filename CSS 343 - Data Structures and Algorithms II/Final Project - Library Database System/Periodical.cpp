#include "Periodical.h"

Periodical::Periodical() {
	genre = "P";
	totalNumber = 1;
	nAvail = 1;
}

Periodical::~Periodical() {
	delete this;
}

ostream& Periodical::print(ostream & output) const {
	output << genre << " " << title << ", " << month << " " << year << endl;
	return output;
}

void Periodical::create(istream &infile) {
	infile.get();
	getline(infile, title, ',');

	infile >> month;
	infile >> year;

}

bool Periodical::operator<(const Book& book) const {
	const Periodical& yBook = static_cast<const Periodical&>(book);
	if (year < yBook.year) {
		return true;
	}
	else if (year > yBook.year) {
		return false;
	}
	else {
		if (month < yBook.month) {
			return true;
		}
		else if (month > yBook.month) {
			return false;
		}
		else {
			if (title < yBook.title) {
				return true;
			}else {
				return false;
			}
		}
	}
}

bool Periodical::operator>(const Book& book) const {
	const Periodical& yBook = static_cast<const Periodical&>(book);
	if (year > yBook.year) {
		return true;
	}
	else if (year < yBook.year) {
		return false;
	}
	else {
		if (month > yBook.month) {
			return true;
		}
		else if (month < yBook.month) {
			return false;
		}
		else {
			if (title > yBook.title) {
				return true;
			}
			else {
				return false;
			}
		}
	}

}

bool Periodical::operator==(const Book& book) const {
	const Periodical& yBook = static_cast<const Periodical&>(book);
	return (year == yBook.year && month == yBook.month && title == yBook.title);
}