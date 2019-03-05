#include "Patron.h"


Patron::Patron() {

}

Patron::~Patron() {
}

void Patron::create(istream& infile, int iden) {
	id = iden;
	infile >> lName;
	infile >> fName;
}

void Patron::addToHist(interaction*) const {

}

void Patron::displayHistory() const {
	node* curr = root;
	while (curr != nullptr) {
		cout << curr->data;
	}
}

void Patron::deleteHistory(node* n) {
	while (n != nullptr) {
		node* temp = n;
		n = n->next;
		delete temp;
	}
}
