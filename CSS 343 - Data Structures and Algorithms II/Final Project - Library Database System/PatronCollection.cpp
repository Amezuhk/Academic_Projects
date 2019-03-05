#include "PatronCollection.h"

PatronCollection::PatronCollection() {
	for (int i = 0; i < 211; i++) {
		pHashArray[i].id = -1;
	}
}

PatronCollection::~PatronCollection() {
}

void PatronCollection::insertAll(istream& infile) {
	for (;;) {
		int id;
		infile >> id;
		if (infile.eof())
			break;
		pHashArray[Hash(id)].create(infile, id);
	}
}

int PatronCollection::Hash(int id) {
	int hash;
	hash = id % 10;
	if (pHashArray[hash].id > 0) {
		if (pHashArray[hash].id == id) {
			return hash;
		}
		int i = 1;
		int h1 = hash;
		int h2 = Hash2(id);
		while (pHashArray[hash].id > 0) {
			hash = h1 + (i * h2);
			if (hash > 211) {
				hash = hash % 211;
			}
			i++;
		}
		return hash;
	}
	else {
		return hash;
	}

}

int PatronCollection::Hash2(int id) {
	return 7 - (id % 7);

}

void PatronCollection::displayP() {
	for (int i = 0; i < 211; i++) {
		if (pHashArray[i].id < 0) {

		}
		else {
			cout << "hash: " << i << " Patron: " << pHashArray[i].id << " " << pHashArray[i].lName 
				<< " " << pHashArray[i].fName << endl;
		}
	}
}