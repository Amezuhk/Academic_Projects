#include "Factory.h"
#include "Youth.h"
#include "Fiction.h"
#include "Periodical.h"

Factory::Factory() {

}

Factory::~Factory() {

}

Fiction* Factory::createFic() {
	return new Fiction;
}

Periodical* Factory::createPer() {
	return new Periodical;
}

Youth* Factory::createYouth() {
	return new Youth;
}

Book* Factory::createBook(char type) {
	if (type == 'F') {
		return createFic();
	}
	else if (type == 'P') {
		return createPer();
	}
	else if (type == 'Y') {
		return createYouth();
	}
	else {
		return nullptr;
	}
}
