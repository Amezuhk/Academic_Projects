#pragma once
#include "Interaction.h"
class Checkout : public Interact {

	virtual void create(istream infile) const;
	virtual Book* getBook() const;
	virtual Patron* getPatron() const;
	virtual void  execute();

};