#include "Fiction.h"

Fiction::Fiction() {
	genre = "F";
	totalNumber = 5;
	nAvail = 5;
}

Fiction::~Fiction() {
	delete this;
}

ostream& Fiction::print(ostream & output) const {
	output << genre << " " << author << ", " << title << ", " << year << endl;
	return output;
}

void Fiction::create(istream &infile) {
	infile.get();
	getline(infile, author, ',');

	infile.get();
	getline(infile, title, ',');

	infile >> year;

}

bool Fiction::operator<(const Book& book) const {
	const Fiction& yBook = static_cast<const Fiction&>(book);
	if (author < yBook.author) {
		return true;
	}
	else if (author > yBook.author) {
		return false;
	}
	else {
		if (title < yBook.title) {
			return true;
		}
		else if (title > yBook.title) {
			return false;
		}
		else {
			return false;
		}
	}

}

bool Fiction::operator>(const Book& book) const {
	const Fiction& yBook = static_cast<const Fiction&>(book);
	if (author > yBook.author) {
		return true;
	}
	else if (author < yBook.author) {
		return false;
	}
	else {
		if (title > yBook.title) {
			return true;
		}
		else if (title < yBook.title) {
			return false;
		}
		else {
			return false;
		}
	}

}

bool Fiction::operator==(const Book& book) const {
	const Fiction& yBook = static_cast<const Fiction&>(book);
	return (author == yBook.author) && (title == yBook.title);
}