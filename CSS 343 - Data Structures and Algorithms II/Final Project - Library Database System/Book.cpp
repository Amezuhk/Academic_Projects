#include "Book.h"

ostream& operator<<(ostream& output, const Book& book) {
	return book.print(output);
}

ostream& Book::print(ostream& output) const {
	return output;
}

Book::Book() {
}
Book::~Book() {
	delete this;
}