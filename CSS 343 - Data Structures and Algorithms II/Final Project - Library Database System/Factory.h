#pragma once
#include <string>
using namespace std;
class Book;
class Fiction;
class Periodical;
class Youth;

class Factory {

public:
	Factory();
	~Factory();
	Book* createBook(char type);
private:
	Fiction* createFic();
	Youth* createYouth();
	Periodical* createPer();
};