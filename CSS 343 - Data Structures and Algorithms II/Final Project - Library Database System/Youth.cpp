#include "Youth.h"

Youth::Youth() {
	genre = "Y";
	totalNumber = 5;
	nAvail = 5;
}

Youth::~Youth(){
	delete this;
}

ostream& Youth::print(ostream & output) const {
	output << genre << " " << author << ", " << title << ", " << year << endl;
	return output;
}

void Youth::create(istream &infile) {
	infile.get();
	getline(infile, author, ',');

	infile.get();
	getline(infile, title, ',');

	infile >> year;

}


bool Youth::operator<(const Book& book) const {
	const Youth& yBook = static_cast<const Youth&>(book);
	if (title < yBook.title) {
		return true; 
	}
	else if (title > yBook.title) {
		return false;
	}
	else {
		if (author < yBook.author) {
			return true;
		}
		else if (author > yBook.author) {
			return false;
		}
		else {
			return false;
		}
	}

}

bool Youth::operator>(const Book& book) const {
	const Youth& yBook = static_cast<const Youth&>(book);
	if (title > yBook.title) {
		return true;
	}
	else if (title < yBook.title) {
		return false;
	}
	else {
		if (author > yBook.author) {
			return true;
		}
		else if (author < yBook.author) {
			return false;
		}
		else {
			return false;
		}
	}

}

bool Youth::operator==(const Book& book) const {
	const Youth& yBook = static_cast<const Youth&>(book);
	return (title == yBook.title) && (author == yBook.author);
}