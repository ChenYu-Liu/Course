#ifndef TERM_H
#define TERM_H

#include <string>
using std::string;


class Iterator;
class Term{
public:
	virtual string symbol() const = 0;
	virtual string value() const;
	virtual bool match(Term & term);
	virtual bool IsVariable();

	virtual bool IsList();

	//Iterator methode
	virtual Iterator * createIterator();
	virtual Iterator * createDFSIterator();
	virtual Iterator * createBFSIterator();

};

#endif
