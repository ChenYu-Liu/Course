#ifndef TERM_H
#define TERM_H

#include <string>
using std::string;

template<class T>
class Iterator;

class Term{
public:
	virtual string symbol() const = 0;
	virtual string value() const;
	virtual bool match(Term& term);
	virtual bool IsVariable();

	virtual bool IsList();

	//Iterator methode
	virtual Iterator<Term*>* createIterator();
	virtual Iterator<Term*>* createDFSIterator();
	virtual Iterator<Term*>* createBFSIterator();

};

#endif
