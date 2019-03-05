#pragma once
#include <string>
#include <iostream>
using namespace std;

class interaction;

class Patron {
public:
	int id;
	Patron();
	~Patron();
	string lName;
	string fName;
	void create(istream &, int);
	void displayHistory() const;
	void addToHist(interaction*) const;
private:
	struct node {
		int data;
		node* next;
	};
	void deleteHistory(node* n);
	node* root;
};