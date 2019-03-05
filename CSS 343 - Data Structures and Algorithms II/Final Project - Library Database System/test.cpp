#include "BookCollection.h"
#include "PatronCollection.h"

int main() {
	//const Apple& anApple = static_cast<const Apple&>(theFruit);   // C++ way
	ifstream infile("data4patrons.txt");
	if (!infile) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	ifstream infile1("data4books.txt");
	if (!infile1) {
		cout << "File could not be opened." << endl;
		return 1;
	}
	
	BookCollection myBooks;
	myBooks.insertAll(infile1);
	cout << myBooks;

	PatronCollection myPatrons = PatronCollection();
	myPatrons.insertAll(infile);
	myPatrons.displayP();

}

