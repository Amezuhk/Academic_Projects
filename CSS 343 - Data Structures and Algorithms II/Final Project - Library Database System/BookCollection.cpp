#include "BookCollection.h"

BookCollection::BookCollection() {

}

BookCollection::~BookCollection() {

}

void BookCollection::insertAll(istream& infile) {
	char ident;
	string line;
	for (;;) {
		infile >> ident;
		if (infile.eof())
			break;
		toInsert = bookFactory.createBook(ident);
		if (toInsert == nullptr) {
			getline(infile, line);
		}
		else {
			toInsert->create(infile);
			int H = Hash(ident);
			hashArray[H].insert(toInsert);
		}
	}

}

int BookCollection::Hash(char toHash) const {
	return toHash - 64;
}

ostream & operator<<(ostream & output, const BookCollection& myCollection) {
	int H = myCollection.Hash('Y');
	output << myCollection.hashArray[H];
	 H = myCollection.Hash('P');
	output << myCollection.hashArray[H];
	 H = myCollection.Hash('F');
	 output << myCollection.hashArray[H];
		return output;
}
